<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_page extends module_template
{
	function display ()
	{
		current_page('page');
		
		if (!user('logged'))
			return login_req();
		

		$data = ldb_select_one('page','*',input(1),'name');
		
		if (!$data)
			return core_error_404();
		
		page_title($data['title']);
		site_title($data['title']);
		
		$out = '';
		$out .= $data['text'];		
		return $out;
	}
}
?>