<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_f extends module_template
{
	function display()
	{
		current_page('f');
		page_title(lang('fl_mylist'), URL . '/files/');
		
		
		$out = '';
		$public = false;
		
		if (input(2))
			$public = true;
		
		$sid = input(1);
		$u_data = ldb_select_one('upload', '*', $sid, 'code');
		
		if (!$u_data) {
			return core_error_404();
		}
		
		$GLOBALS['core']->public_wdg = !$public;
		
		if ($u_data['uid'] != user('id')) {
			if (!input(2, $u_data['ph'])) {
				return core_error_404();
			} else {
				# Public page view...
			}
		}
		
		$own = $u_data['uid'] == user('id');
		
		if ($own && @$_POST['sub_edit'] && @$_GET['k'] = md5(user('lk'))) {
			return $this->edit($u_data);
		}
		if ($own && @$_GET['del'] && @$_GET['k'] = md5(user('lk'))) {
			return $this->del($u_data);
		}
		
		page_title(sprintf(lang('fld_title_n'), $u_data['id']));
		
		$f_data = ldb_select('file', '*', '`upid`=' . $u_data['id']);
		
		
		$u_data['time_added'] = date('d.m.Y H:i', $u_data['tms_upload']);
		$u_data['time_del'] = time_delete($u_data['tms_upload'], $u_data['tms_delete']);
		$u_data['user'] = user_link($u_data['uid']);
		$u_data['descr'] = htmlspecialchars($u_data['comment']);
		
		$f_list = '';
		for ($x = 0; $x < count($f_data); $x++) {
			$f_link = URL . '/c/d/' . $u_data['code'] . '/' . $f_data[ $x ]['upn'] . '/' . $f_data[ $x ]['dh'] . '/' . htmlspecialchars($f_data[ $x ]['file_name']);
			$f_flink = URL . '/c/f/' . $u_data['code'] . '/' . $f_data[ $x ]['upn'] . '/' . $f_data[ $x ]['dh'] . '/' . htmlspecialchars($f_data[ $x ]['file_name']);
			
			$fd = $f_data[ $x ];
			$fd['size'] = format_size($fd['file_size']);
			$fd['name'] = htmlspecialchars($fd['file_name']);
			
			$tpl = new ltpl ('download-file-item');
			$tpl->v('f', $fd);
			$tpl->v('f_link', $f_link);
			$tpl->v('f_link_f', $f_flink);
			
			# Get file icon
			$f_icon = get_icon($fd['file_ext']);
			$tpl->v('f_icon', $f_icon);
			
			$f_list .= $tpl->get();
		}
		
		include_once CORE_PATH . '/ttl.php';
		$ttl_s = '';
		foreach ($GLOBALS['ttl'] as $tm => $tt)
			$ttl_s .= '<option value="' . $tm . '"' . ($tm == $u_data['ttl'] ? ' selected="selected"' : '') . '>' . $tt . '</option>';
		
		$u_data['publink'] = URL . '/f/' . $u_data['code'] . '/' . $u_data['ph'] . '/';
		
		$tpl = new ltpl ('download-file');
		$tpl->v('u_data', $u_data);
		$tpl->v('f_list', $f_list);
		$tpl->v('ttl_sel', $ttl_s);
		$tpl->v('own', $u_data['uid'] == user('id'));
		$out .= $tpl->get();
		
		return $out;
	}
	
	function edit($data)
	{
		include_once CORE_PATH . '/ttl.php';
		$ttl = @$_POST['files_ttl'];
		if (!isset($GLOBALS['ttl'][ $ttl ]))
			$ttl = $GLOBALS['ttl_def'];
		
		$db_data = array();
		if (@$_POST['files_ttl_prol']) {
			$db_data['prolong'] = 'Y';
			$db_data['tms_delete'] = $data['tms_last'] + $ttl;
		} else {
			$db_data['prolong'] = 'N';
			$db_data['tms_delete'] = $data['tms_upload'] + $ttl;
		}
		$db_data['ttl'] = $ttl;
		$db_data['comment'] = @$_POST['files_descr'];
		ldb_update_by_id('upload', $data['id'], $db_data);
		
		redirect_msg(URL . '/f/' . $data['code'] . '/?', lang('save_ok'));
		exit();
	}
	
	function del($data)
	{
		ldb_query('DELETE FROM `upload` WHERE `id`=' . $data['id']);
		redirect_msg(URL . '/files/', lang('delete_ok'));
		exit();
	}
}

?>