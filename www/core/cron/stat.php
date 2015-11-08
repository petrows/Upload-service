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
		$data = kdb_select('upload','*','1');
		foreach ($data as $d)
			$this->process_upload($d);
		
		kdb_query('UPDATE `upload` SET `tms_delete`=`tms_last`+`ttl` WHERE `prolong`=\'Y\'');
	}
	
	function process_upload($data)
	{
		# Get last download time
		$path = ROOT_PATH.'/d/'.substr($data['code'],0,2).'/'.substr($data['code'],2);
		
		$flist = kdb_select('file','*','`upid`='.$data['id']);
		$mtimes = array ();
		foreach($flist as $f)
		{
			$mt = @filemtime($path.'/'.$f['upn'].'.dt');
			if (!$mt) continue;
			
			$mtimes[] = $mt;
			kdb_query('UPDATE `file` SET `tms_last`='.$mt.' WHERE `id`='.$f['id'].' LIMIT 1');
		}
		
		kdb_query('UPDATE `upload` SET `tms_last`='.min($mtimes).' WHERE `id`='.$data['id'].' LIMIT 1');
	}
}

$c = new st();
$c->run();

?>