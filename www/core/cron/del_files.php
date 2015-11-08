<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

require dirname(__FILE__).'/cron_init.php';

class del_files
{
	function run ()
	{
		# 1. Update all files data
		kdb_query('UPDATE `upload` SET `file_count`=(SELECT COUNT(*) FROM `file` WHERE `file`.`upid`=`upload`.`id`),`file_size`=(SELECT SUM(`file_size`) FROM `file` WHERE `file`.`upid`=`upload`.`id`)');
		# 2. Remove upload-files by TTL-time
		kdb_query('DELETE FROM `upload` WHERE `tms_delete`<'.time().' OR `file_count`=0');
		# 3. Remove files by no-parent
		kdb_query('DELETE FROM `file` WHERE `file`.`upid` NOT IN (SELECT `id` FROM `upload`)');
		
		# 4. Scan folders by no-parent uploads
		$this->clean_d();
		
		$this->clean_dir('/tmp/upload', 24*3600);
		$this->clean_dir('/tmp/sid', 24*3600);
		$this->clean_dir('/tmp/sid_api', 24*3600);
	}
	
	function clean_d ()
	{
		$dh1 = opendir(ROOT_PATH.'/d/');
		if (!$dh1) return; # Error
		while (($file1=readdir($dh1))!==false)
		{
			if ($file1[0] == '.' || !is_dir(ROOT_PATH.'/d/'.$file1)) continue; # Hidden
			
			# Clean sub-d level 1
			$dh2 = opendir(ROOT_PATH.'/d/'.$file1);
			if (!$dh2) continue; # Error
			while (($file2=readdir($dh2))!==false)
			{
				if ($file2[0] == '.' || !is_dir(ROOT_PATH.'/d/'.$file1.'/'.$file2)) continue; # Hidden
				
				# Okay, we got key!
				$code = $file1.$file2;
				$res = kdb_select_one('upload', array('id'), $code, 'code');
				
				if (!$res && !kdb_error())
				{
					# Delete this fuck'n file
					echo 'Deleting: '.ROOT_PATH.'/d/'.$file1.'/'.$file2."\n";
					recursive_remove_directory(ROOT_PATH.'/d/'.$file1.'/'.$file2);					
				}
			}
		}
	}
	
	function clean_dir($path, $tms_delete)
	{
		$dh1 = opendir(ROOT_PATH.$path);
		if (!$dh1) return; # Error
		while (($file1=readdir($dh1))!==false)
		{
			if ($file1[0] == '.') continue; # Hidden
			
			if (filemtime(ROOT_PATH.$path.'/'.$file1) < (time()-($tms_delete)))
			{
				# Remove old file!
				echo 'Deleting: '.ROOT_PATH.$path.'/'.$file1."\n";
				unlink(ROOT_PATH.$path.'/'.$file1);
			}
		}
	}
}

$c = new del_files();
$c->run();

?>