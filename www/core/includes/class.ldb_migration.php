<?php

require_once CORE_PATH . '/includes/class.ldb.php';

abstract class ldb_migration_base {

	public abstract function run();

	protected function select_db($config) {
		ldb_cfg_select($config);
	}

	protected function query($query) {
		cli_log("Query: $query");
		ldb_query($query);
	}

	protected function exec($command, $critical = true) {
		cli_log("Command: $command");
		$exec_code = 155;
		$exec_ret = system($command, $exec_code);
		if (!$exec_ret || 0 != $exec_code) {
			cli_error("Command returned $exec_code");
			if ($critical) {
				throw new Exception("Exec command error");
			}
		}
	}

}

class ldb_migration {

	private $schemaTableName = '_schema_version';
	private $versions; # Versions in current DB Schema
	private $migrationsFilesystem; # versions in VCS

	public function __construct() {
		# Create table if needed
		$this->recreateRevTable();
		$this->loadCurrentRevision();
	}

	private function recreateRevTable() {
		$sql_create = <<<SQL
CREATE TABLE IF NOT EXISTS `{$this->schemaTableName}` (
  `id` bigint(20) NOT NULL,
  `tms` bigint(20) NOT NULL,
  `log` text NOT NULL,
  PRIMARY KEY (`id`)
)
SQL;

		ldb_query($sql_create);
	}

	private function loadCurrentRevision() {
		$this->versions = ldb_select($this->schemaTableName, array('id', 'tms'), '1 ORDER BY `id` ASC');
		$this->versions = ldb_id2key($this->versions);
	}

	private function loadFileRevisions() {
		$this->migrationsFilesystem = array();

		$dh = opendir(ROOT_PATH . '/deploy/migrations/');
		if (!$dh) {
			cli_error("Migrations dir failed open");
			return false;
		}

		while (($file = readdir($dh)) !== false) {
			if ('.' == $file || '..' == $file)
				continue;
			if (!preg_match('/^(\d+)\.php$/', $file, $m))
				continue;

			$migration_id = intval($m[1]);

			# Skip already applyed migration
			if (isset($this->versions[$migration_id])) {
				# cli_log("Version id $migration_id already in schema");
				continue;
			}

			$this->migrationsFilesystem[$migration_id] = array();
			require_once ROOT_PATH . '/deploy/migrations/' . $migration_id . '.php';
			$obj_class = "migration_" . $migration_id;
			if (!is_subclass_of($obj_class, 'ldb_migration_base')) {
				cli_error("Migration $migration_id wrong class/parent class");
				return false;
			}
			$this->migrationsFilesystem[$migration_id] = new $obj_class();
		}

		ksort($this->migrationsFilesystem);

		return true;
	}

	public function migrate() {
		# Get revisions from FS
		if (!$this->loadFileRevisions()) {
			return false; # Error?
		}

		if (!$this->migrationsFilesystem) {
			# Nothing to migrate
			cli_log("Up-to-date or nothing to migrate");
			return true;
		}

		cli_log("Pending migrations: " . count($this->migrationsFilesystem));

		foreach ($this->migrationsFilesystem as $id => $migrat) {
			cli_log("Apply migration ID $id");
			if (!$migrat->run()) {
				cli_error("Error return code in migration $id");
				exit(1);
			}

			# Save migration ID
			ldb_insert($this->schemaTableName, array('id' => $id, 'tms' => time()));
		}
		cli_log("Migration OK!");
		return true;
	}

}
