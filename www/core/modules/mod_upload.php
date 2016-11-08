<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_upload extends module_template
{
	public $file;
	public $sid;
	
	function display()
	{
		current_page('upload');
		
		if (!user('logged')) {
			# Login req
			return login_req();
		}
		
		if (!@$_COOKIE['usid']) {
			setcookie('usid', md5(microtime(true) . mt_rand() . md5(sha1(time()) . microtime(true)) . mt_rand()), time() + 86400, '/', COOKIE_DOMAIN);
		} else {
			setcookie('usid', $_COOKIE['usid'], time() + 86400, '/', COOKIE_DOMAIN);
		}
		
		if (!$this->check_sid()) {
			// Generate new SID
			return $this->new_sid();
		}
		
		if (input(1, 'complete')) return $this->complete();
		if (input(1, 'final')) return $this->get_final();
		
		# Form - reset status
		if (ldb_select_one('upload', array('id'), $this->sid, 'code')) {
			return $this->new_sid();
		}
		
		# Default - show form
		$tpl = new ltpl ('upload');
		
		# Get ext table
		$ext_t = '';
		$ext_js = array();
		if (cfg('ext_control')) {
			foreach ($GLOBALS['ext'] as $eg) {
				$ext_t .= '<div class="ext_t"><h3>' . $eg['t'] . ':</h3><ul>';
				foreach ($eg['d'] as $ed) {
					$ext_t .= '<li><b>' . $ed[0] . '</b> (' . implode(', ', $ed[1]) . ')</li>';
					$ext_js = array_merge($ext_js, $ed[1]);
				}
				$ext_t .= '</ul></div>';
			}
		}
		include_once CORE_PATH . '/ttl.php';
		$ttl_s = '';
		foreach ($GLOBALS['ttl'] as $tm => $tt)
			$ttl_s .= '<option value="' . $tm . '"' . ($tm == $GLOBALS['ttl_def'] ? ' selected="selected"' : '') . '>' . $tt . '</option>';
		
		$tpl->v('sid', $this->sid);
		$tpl->v('ext_t', $ext_t);
		$tpl->v('ext_js', '\'' . implode('\',\'', $ext_js) . '\'');
		$tpl->v('max_size', user_max_size());
		$tpl->v('ttl_sel', $ttl_s);
		
		return $tpl->get();
	}
	
	function new_sid()
	{
		@header('Location: ' . URL . '/upload/?s=' . md5(md5(sha1(time()) . microtime(true)) . mt_rand()));
		exit();
	}
	
	function check_sid()
	{
		$sid = trim(@$_GET['s']);
		if (!preg_match('/^[a-f0-9]{32}$/', $sid)) {
			return false;
		}
		// Check The SID
		if (!file_exists(ROOT_PATH . '/tmp/sid/' . md5($sid))) {
			// Create new session!
			file_put_contents(ROOT_PATH . '/tmp/sid/' . md5($sid), user('id') . ':' . $_SERVER['REMOTE_ADDR'] . ':' . $sid . ':' . user('lk') . ':' . user_max_size());
			@chmod(ROOT_PATH . '/tmp/sid/' . md5($sid), 0777);
			$this->sid = $sid;
			
			return true;
		} else {
			$dt = explode(':', file_get_contents(ROOT_PATH . '/tmp/sid/' . md5($sid)));
			if (@$dt[0] != user('id') || @$dt[1] != $_SERVER['REMOTE_ADDR'] || @$dt[2] != $sid || @$dt[3] != user('lk')) {
				return false;
			}
			$this->sid = $sid;
			
			return true;
		}
	}
	
	function complete()
	{
		$id = intval(@$_GET['id']);
		
		include_once CORE_PATH . '/ttl.php';
		
		# Check file
		$f_in = ROOT_PATH . '/tmp/upload/' . md5($this->sid) . '-' . $id;
		if (!file_exists($f_in)) {
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_int') . ' (F_E)')), ENT_NOQUOTES));
		}
		
		# Size...
		
		# Name...
		$fname = trim(basename(@$_GET['qqfile']));
		if (!$fname)
			$fname = 'ass.txt';
		
		# Check extension
		$finfo = pathinfo($fname);
		$ext = strtolower($finfo['extension']);
		if (!ext_allowed($ext))
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_ntype'))), ENT_NOQUOTES));
		
		# Okay...
		$fname = preg_replace('!<>\\/\n\r\t!', '', $fname);
		$ph = substr(sha1(md5(microtime(true)) . mt_rand() . md5($fname . $fname)), 4, 8);
		
		$ttl = $GLOBALS['ttl_def'];
		$tms_del = time() + $ttl;
		
		# Create DB record
		try {
			ldb_insert('upload', array('uid' => user('id'), 'code' => $this->sid, 'ph' => $ph, 'tms_upload' => time(), 'tms_last' => time(), 'tms_delete' => $tms_del, 'ttl' => $ttl));
		} catch (Exception $e) {
			
		}
		
		$rec = ldb_select('upload', '*', '`uid`=' . user('id') . ' AND `code`=\'' . $this->sid . '\' LIMIT 1');
		$rec = @$rec[0];
		if (!$rec) {
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_int') . ' (D_E)')), ENT_NOQUOTES));
		}
		
		# Create uploading DIR
		$u_dir = ROOT_PATH . '/d/' . substr($this->sid, 0, 2);
		@mkdir($u_dir);
		@chmod($u_dir, 0777);
		$u_dir .= '/' . substr($this->sid, 2);
		@mkdir($u_dir);
		@chmod($u_dir, 0777);
		#$u_dir .= '/'.$id;
		#@mkdir($u_dir);
		
		if (!file_exists($u_dir)) {
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_int') . ' (DR_E)')), ENT_NOQUOTES));
		}
		
		# Copy file!
		if (!copy($f_in, $u_dir . '/' . $id . '.dat')) {
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_int') . ' (CP_E)')), ENT_NOQUOTES));
		}
		
		@unlink($f_in);
		
		# Make simlink...
		#chdir($u_dir);
		#system('ln -s '.escapeshellarg('./'.$fname).' '.escapeshellarg('./file.'.$finfo['extension']));
		
		$fmime = get_mime_type($fname);
		$fsize = filesize_fix($u_dir . '/' . $id . '.dat');
		$dh = substr(sha1(md5(microtime(true)) . mt_rand() . md5($fname . $fmime)), 8, 8);
		
		# Add to DB!		
		$file_id = ldb_insert('file', array('uid' => user('id'), 'upid' => $rec['id'], 'upn' => $id, 'dh' => $dh, 'file_name' => $fname, 'file_ext' => $ext, 'file_size' => $fsize, 'tms_add' => time(), 'tms_last' => time()));
		if (!$file_id) {
			return exit(htmlspecialchars(json_encode(array('error' => lang('fl_e_int') . ' (DB_E)')), ENT_NOQUOTES));
		}
		
		ldb_query('UPDATE `upload` SET `file_count`=`file_count`+1, `file_size`=`file_size`+' . $fsize . ' WHERE `id`=' . $rec['id']);
		# return exit(htmlspecialchars(json_encode(array('error'=>  ldb_log_html())), ENT_NOQUOTES));
		
		# Make info file
		$inf = array();
		$inf[] = $fname;
		$inf[] = $fmime;
		$inf[] = $file_id;
		$inf[] = $fsize;
		$inf[] = $dh;
		
		file_put_contents($u_dir . '/' . $id . '.inf', implode("\n", $inf));
		@chmod($u_dir . '/' . $id . '.dat', 0777);
		@chmod($u_dir . '/' . $id . '.inf', 0777);
		
		exit(htmlspecialchars(json_encode(array('success' => true)), ENT_NOQUOTES));
	}
	
	function get_final()
	{
		# Okay, remove th SID
		@unlink(ROOT_PATH . '/tmp/sid/' . md5($this->sid));
		
		# Check upload data
		$u_data = ldb_select_one('upload', '*', $this->sid, 'code');
		if (!$u_data || $u_data['uid'] != user('id'))
			return core_error_404();
		
		include_once CORE_PATH . '/ttl.php';
		$ttl = @$_POST['files_ttl'];
		if (!isset($GLOBALS['ttl'][ $ttl ]))
			$ttl = $GLOBALS['ttl_def'];
		
		$tms_del = $u_data['tms_last'] + $ttl;
		$ttl_p = @$_POST['files_ttl_prol'] ? 'Y' : 'N';
		
		# Update TTL
		ldb_update_by_id('upload', $u_data['id'], array('tms_delete' => $tms_del, 'ttl' => $ttl, 'prolong' => $ttl_p, 'comment' => @$_POST['files_descr']));
		ldb_query('UPDATE `upload` SET `file_count`=(SELECT COUNT(*) FROM `file` WHERE `file`.`upid`=`upload`.`id`),`file_size`=(SELECT SUM(`file_size`) FROM `file` WHERE `file`.`upid`=`upload`.`id`) WHERE `id`=' . $u_data['id']);
		
		# Redirect to the file control...
		@header('Location: ' . URL . '/f/' . $this->sid . '/');
	}
}

?>