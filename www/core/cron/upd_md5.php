<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

require dirname(__FILE__).'/cron_init.php';

class st
{
	function run ()
	{
		$data = ldb_select('client_version','*','1');
		foreach ($data as $d)
			$this->process_dir(ROOT_PATH.'/client/v/'.$d['ver']);
	}
	
	function process_dir($d)
	{
		$dh = opendir($d);
		if (!$dh) return;
		
		while (($file=readdir($dh))!==false)
		{
			if ($file == '.' || $file == '..' || preg_match('/\.md5$/',$file)) continue;
			if (is_dir($d.'/'.$file))
			{
				$this->process_dir($d.'/'.$file);
				continue;
			}
			echo 'Processing file: '.$d.'/'.$file."\n";
			file_put_contents($d.'/'.$file.'.md5',md5_file($d.'/'.$file));
		}
	}
}

$c = new st();
$c->run();

?>