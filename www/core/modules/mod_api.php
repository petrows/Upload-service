<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_api extends module_template
{
	public $sid;
	public $uid;
	public $lk;
	
	function display ()
	{
		@header('Content-Type: text/xml');
		echo '<?xml version="1.0" encoding="UTF-8"?>'."\n";
		echo '<api>'."\n";
		$this->run_api();
		echo '</api>'."\n";
		exit();		
	}
	
	function run_api ()
	{
		
		if (@$_GET['a']=='init')
			return $this->init();
		if (@$_GET['a']=='check')
			return $this->check();
		
		if (!$this->check_sid(0))
		{
			return $this->error('SID_ERROR','Invalid session - restart your program');
		}
		
		include_once CORE_PATH.'/ttl.php';

		if (@$_GET['a']=='client-update')
			return $this->soft_update();

		if (@$_GET['a']=='upload-done' || input(1,'upload-done'))
			return $this->upload_complete();
		if (@$_GET['a']=='update')
			return $this->update();
		if (@$_GET['a']=='delete')
			return $this->delete();
		
		return $this->error('UNK_METHOD',"Unknown API Method");
	}
	
	function error ($code, $text)
	{
		echo '<error code="'.$code.'">'.htmlspecialchars($text).'</error>';
	}
	
	function check ()
	{
		$login = @$_COOKIE['login'];
		$passw = @$_COOKIE['passw'];

		$uid = user_password($login,$passw,true);
		if (!$uid)
		{
			return $this->error('LOGIN_ERROR','Invalid login or password');
		}
		echo '<ok>OK</ok>';
	}
	
	function init ()
	{
		# Okay, init user session with it's login & password
		$login = @$_COOKIE['login'];
		$passw = @$_COOKIE['passw'];

		$uid = user_password($login,$passw,true);
		if (!$uid)
		{
			return $this->error('LOGIN_ERROR','Invalid login or password');
		}
		
		$uinfo = user_info($uid);
		
		$this->make_sid($uid);
		
		# Generate SID
		echo '<user>';
		echo '<sid>'.$this->sid.'</sid>';
		echo '<lk>'.($this->lk).'</lk>';
		echo '<uid>'.$uid.'</uid>';
		echo '<name>'.htmlspecialchars($uinfo['name']).'</name>';
		echo '<seed>'.mt_rand().'</seed>';
		echo '</user>'."\n";
		
		# Version info
		if (@$_COOKIE['v'] && @$_COOKIE['os'])
		{
			$ver = explode('.',$_COOKIE['v']);
			$ver = sprintf('%02d%02d%02d',@$ver[0],@$ver[1],@$ver[2]);
			$ver = intval($ver);
			$os  = preg_replace('/[^a-z0-9]/','',strtolower($_COOKIE['os']));
			# Check version
			$lastv = ldb_select('client_version',array('ver','veri','tms_publish'),'`veri`>'.$ver.' AND `os_'.$os.'`=\'Y\' AND `published`=\'Y\' ORDER BY `veri` DESC LIMIT 1');
			$lastv = @$lastv[0];
			
			if ($lastv)
			{
				echo '<newversion ver="'.$lastv['ver'].'" tms_publish="'.$lastv['tms_publish'].'"/>'."\n";
			}
		}
		
		include_once CORE_PATH.'/ttl.php';
		echo '<ttl default="'.$GLOBALS['ttl_def'].'">'."\n";
		foreach ($GLOBALS['ttl'] as $k=>$v)
		{
			echo '<rec name="'.htmlspecialchars($v).'" value="'.$k.'"'.($k==$GLOBALS['ttl']?' default="default"':'').'/>'."\n";
		}
		echo '</ttl>'."\n";
		
		# Get file list...
		$u_list = ldb_select ('upload','*', '`uid`='.$uid.' ORDER BY `tms_upload` ASC');
		echo '<uploads>'."\n";
		for ($x=0;$x<count($u_list);$x++)
		{
			echo '<upload id="'.$u_list[$x]['id'].'" code="'.$u_list[$x]['code'].'" ph="'.$u_list[$x]['ph'].'" comment="'.htmlspecialchars($u_list[$x]['comment']).'" tms_upload="'.$u_list[$x]['tms_upload'].'" tms_last="'.$u_list[$x]['tms_last'].'" ttl="'.$u_list[$x]['ttl'].'" tms_delete="'.$u_list[$x]['tms_delete'].'" prolong="'.($u_list[$x]['prolong']=='Y'?1:0).'">';
			echo '<files>';
			$f_list = ldb_select('file','*','`upid`='.$u_list[$x]['id'].' ORDER BY `tms_add` ASC');
			for ($f=0;$f<count($f_list);$f++)
			{
				echo '<file id="'.$f_list[$f]['id'].'" n="'.$f_list[$f]['upn'].'" dh="'.$f_list[$f]['dh'].'" name="'.htmlspecialchars($f_list[$f]['file_name']).'" size="'.$f_list[$f]['file_size'].'" tms_add="'.$f_list[$f]['tms_add'].'"/>';
			}
			echo '</files>';
			echo '</upload>';
		}
		echo '</uploads>'."\n";
		
		# Save data
		
		
		return;
	}
	
	function make_sid ($uid)
	{
		do {
			$this->sid = md5(mt_rand().md5(time()).microtime().md5(serialize($_SERVER))); 
		} while (file_exists(ROOT_PATH.'/tmp/sid_api/'.md5($this->sid)));
			
		$this->lk = md5(mt_rand().md5(time()).'fuck-off-'.microtime().md5(serialize($_SERVER)));
			
		file_put_contents(ROOT_PATH.'/tmp/sid_api/'.md5($this->sid),$uid.':'.$_SERVER['REMOTE_ADDR'].':'.$this->sid.':'.md5($this->lk).':0');
		@chmod(ROOT_PATH.'/tmp/sid_api/'.md5($this->sid),0777);
	}
	
	function check_sid ($uid)
	{
		$sid = '';
		if (@$_GET['s'])
			$sid = trim($_GET['s']);
		if (@$_COOKIE['sid'])
			$sid = trim($_COOKIE['sid']);
		if (!preg_match('/^[a-f0-9]{32}$/',$sid))
		{
			return false;
		}
		// Check The SID
		if (!file_exists(ROOT_PATH.'/tmp/sid_api/'.md5($sid)))
		{
			return false;
		} else {
			$dt = explode(':',file_get_contents(ROOT_PATH.'/tmp/sid_api/'.md5($sid)));
			if (@$dt[1] != $_SERVER['REMOTE_ADDR'] || @$dt[2] != $sid)
			{
				return false;
			}
			$this->sid = $sid;
			$this->uid = intval(@$dt[0]);
			return true;
		}
	}
	
	function soft_update ()
	{
		$ver = explode('.',@$_COOKIE['v']);
		$ver_c = array(@intval($ver[0]),@intval($ver[1]),@intval($ver[2]));
		$ver = sprintf('%02d%02d%02d',@$ver[0],@$ver[1],@$ver[2]);
		$ver = intval($ver);
		$os  = preg_replace('/[^a-z0-9]/','',strtolower(@$_COOKIE['os']));
		
		$in_flist = array ();
		$in_flist = explode("|",@$_POST['flist']);
		
		# print_r($in_flist);
		
		# Check version
		$v_data = ldb_select('client_version','*','`veri`>'.$ver.' AND `os_'.$os.'`=\'Y\' AND `published`=\'Y\' ORDER BY `veri` DESC');
		$lastv = @$v_data[0];
		
		if (!$lastv)
		{
			echo '<update last="yes"/>';
			return; // No updates
		}
		
		# Get files list
		$flist_root = ROOT_PATH.'/client/v/'.$lastv['ver'].'/'.$os.'/';
		$flist = $this->_upd_flist($flist_root,'/');
		if (!$flist)
		{
			return $this->error('UPD_SERVER_ERROR','Internal error, please try again later!');
		}
		
		echo '<update version="'.$lastv['ver'].'" versioni="'.$lastv['veri'].'" tms_publish="'.$lastv['tms_publish'].'">'."\n";
		echo '<info>';
		for ($x=0; $x<count($v_data); $x++)
		{
			echo '<rel version="'.$v_data[$x]['ver'].'" versioni="'.$v_data[$x]['veri'].'" tms_publish="'.$v_data[$x]['tms_publish'].'"><![CDATA['.$v_data[$x]['comment'].']]></rel>'."\n";
		}
		echo '</info>';
		echo '<files>'."\n";
		for ($x=0; $x<count($flist); $x++)
		{
			$md5 = @file_get_contents($flist_root.$flist[$x].'.md5');
			if (in_array(md5($flist[$x].$md5),$in_flist)) continue; # This file not needs to be updated
			echo '<file n="'.$x.'" name="'.$flist[$x].'" size="'.filesize($flist_root.$flist[$x]).'" md5="'.$md5.'" url="'.htmlspecialchars(URL.'/client/v/'.$lastv['ver'].'/'.$os.''.$flist[$x]).'"/>'."\n";
		}
		echo '</files>'."\n";
		echo '</update>'."\n";
	}
	
	function _upd_flist ($root, $dir)
	{
		$flist = array ();
		$dh1 = opendir($root.$dir);
		if (!$dh1) return; # Error
		while (($file1=readdir($dh1))!==false)
		{
			if ($file1[0] == '.') continue; # Hidden
			if (preg_match('/\.md5$/',$file1)) continue; # MD5-summ
			
			if (is_dir($root.$dir.$file1))
			{
				$flist = array_merge($flist,$this->_upd_flist($root,$dir.$file1.'/'));
			} else {
				$flist[] = $dir.$file1;
			}
		}
		return $flist;
	}
	
	function upload_complete ()
	{
		$up_id = intval(@$_GET['upid']);
		$id    = intval(@$_GET['id']);
	
		include_once CORE_PATH.'/ttl.php';
	
		# Check file
		$f_in = ROOT_PATH.'/tmp/upload/'.md5($this->sid.$up_id).'-'.$id;
		if (!file_exists($f_in))
		{
			return $this->error('UPLOAD_INT_F_E',lang('fl_e_int'));
		}
		
		# Size...
		
		# Name...
		$fname = trim(basename(@$_GET['qqfile']));
		if (!$fname)
			$fname = 'ass.txt';
		
		# Check extension
		$finfo = pathinfo($fname);
		$ext = strtolower(@$finfo['extension']);
		
		if (!ext_allowed($ext))
			return $this->error('UPLOAD_NTYPE',lang('fl_e_ntype'));

		#	return exit(htmlspecialchars(json_encode(array('error'=>lang('fl_e_ntype'))), ENT_NOQUOTES));
		
		# Okay...
		$fname = preg_replace('!<>\\/\n\r\t!','',$fname);
		
		$up_code = md5($this->sid.$up_id);
		$ph = substr(sha1(md5(microtime(true)).mt_rand().md5($fname)),8,8);
		
		$ttl = $GLOBALS['ttl_def'];
		$tms_del = time() + $ttl;
		
		# Create DB record
		ldb_insert('upload', array('uid'=>$this->uid,'code'=>$up_code,'ph'=>$ph,'tms_upload'=>time(),'tms_last'=>time(),'tms_delete'=>$tms_del,'ttl'=>$ttl));
		
		$rec = ldb_select('upload', '*', '`uid`='.$this->uid.' AND `code`=\''.$up_code.'\' LIMIT 1');
		$rec = @$rec[0];
		if (!$rec)
		{
			return $this->error('UPLOAD_INT_D_E',lang('fl_e_int'));
			#return exit(htmlspecialchars(json_encode(array('error'=>lang('fl_e_int').' (D_E)')), ENT_NOQUOTES));
		}
		
		# Create uploading DIR
		$u_dir = ROOT_PATH.'/d/'.substr($up_code,0,2);
		@mkdir($u_dir);
		@chmod($u_dir,0777);
		$u_dir .= '/'.substr($up_code,2);
		@mkdir($u_dir);
		@chmod($u_dir,0777);
		#$u_dir .= '/'.$id;
		#@mkdir($u_dir);
		
		if (!file_exists($u_dir))
		{
			return $this->error('UPLOAD_INT_DR_E',lang('fl_e_int'));
			return exit(htmlspecialchars(json_encode(array('error'=>lang('fl_e_int').' (DR_E)')), ENT_NOQUOTES));
		}
		
		# Copy file!
		if (!copy($f_in,$u_dir.'/'.$id.'.dat'))
		{
			return $this->error('UPLOAD_INT_CP_E',lang('fl_e_int'));
			return exit(htmlspecialchars(json_encode(array('error'=>lang('fl_e_int').' (CP_E)')), ENT_NOQUOTES));
		}
		
		@unlink($f_in);
		
		# Make simlink...
		#chdir($u_dir);
		#system('ln -s '.escapeshellarg('./'.$fname).' '.escapeshellarg('./file.'.$finfo['extension']));
		
		$fmime = get_mime_type($fname);
		$fsize = filesize_fix($u_dir.'/'.$id.'.dat');
		$dh = substr(sha1(md5(microtime(true)).mt_rand().md5($fname.$fmime)),8,8);
				
		# Add to DB!		
		$file_id = ldb_insert('file', array('uid'=>$this->uid,'upid'=>$rec['id'],'upn'=>$id,'dh'=>$dh,'file_name'=>$fname,'file_ext'=>$ext,'file_size'=>$fsize,'tms_add'=>time(),'tms_last'=>time()));
		if (!$file_id)
		{
			return $this->error('UPLOAD_INT_DB_E',lang('fl_e_int'));
			return exit(htmlspecialchars(json_encode(array('error'=>lang('fl_e_int').' (DB_E)')), ENT_NOQUOTES));
		}
		
		ldb_query('UPDATE `upload` SET `file_count`=`file_count`+1, `file_size`=`file_size`+'.$fsize.' WHERE `id`='.$rec['id']);
		# return exit(htmlspecialchars(json_encode(array('error'=>  ldb_log_html())), ENT_NOQUOTES));
		
		# Make info file
		$inf = array ();
		$inf[] = $fname;
		$inf[] = $fmime;
		$inf[] = $file_id;
		$inf[] = $fsize;
		$inf[] = $dh;
		
		file_put_contents($u_dir.'/'.$id.'.inf', implode("\n",$inf));
		@chmod($u_dir.'/'.$id.'.dat',0777);
		@chmod($u_dir.'/'.$id.'.inf',0777);
		
		echo '<upload status="ok" upload_id="'.$rec['id'].'" upload_code="'.$rec['code'].'" upload_ph="'.$rec['ph'].'" tms_delete="'.$rec['tms_delete'].'" ttl="'.$rec['ttl'].'" prolong="'.$rec['prolong'].'" tms_last="'.$rec['tms_last'].'" file_id="'.$file_id.'" file_n="'.$id.'" file_dh="'.$dh.'"/>'."\n";
	}
	
	function update ()
	{
		$id = intval($_GET['id']);
		
		$data = ldb_select_one('upload','*',$id);
		if (!$data || @$data['uid'] != $this->uid)
		{
			return $this->error('UPLOAD_NF','Upload is not found...');
		}
		
		$ttl = $GLOBALS['ttl_def'];
		if (isset($GLOBALS['ttl'][@$_GET['ttl']]))
			$ttl = $_GET['ttl'];
		
		$prol = @$_GET['prol']=='Y'?true:false;
		
		if ($prol)
		{
			$tms_del = time() + $ttl;
		} else {
			$tms_del = $data['tms_upload'] + $ttl;
		}
		
		ldb_query('UPDATE `upload` SET `comment`=\''.ldb_escape(@$_GET['comment']).'\',`prolong`=\''.($prol?'Y':'N').'\',`tms_delete`='.$tms_del.',`ttl`='.$ttl.' WHERE `id`='.$id);
		
		$data = ldb_select_one('upload','*',$id);
		
		echo '<update status="ok" tms_delete="'.$data['tms_delete'].'" ttl="'.$data['ttl'].'" prolong="'.$data['prolong'].'" tms_last="'.$data['tms_last'].'"/>'."\n";
	}
	
	function delete ()
	{
		$id = intval($_GET['id']);
		
		$data = ldb_select_one('upload','*',$id);
		if (!$data || @$data['uid'] != $this->uid)
		{
			return $this->error('UPLOAD_NF','Upload is not found...');
		}
		
		ldb_query('DELETE FROM `upload` WHERE `id`='.$id);
		
		echo '<delete status="ok"/>'."\n";
	}
	
	function delete_file ()
	{
	}
}
?>