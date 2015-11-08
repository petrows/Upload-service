<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_index extends module_template
{
	function display ()
	{
		current_page('index');

		$out = '';
		if (user('logged'))
		{
			$out .= '<div style="padding:20px;text-align:center;font-size:16px;"><a href="'.URL.'/page/client/">Скачать клиент!</a></div>';
			$out .= '<div style="padding:20px;text-align:center;font-size:16px;"><a href="'.URL.'/upload/">'.lang('fl_upload').'</a></div>';
		} else {
			$out .= '<center>Welcommen!</center>';
		}
		return $out;
	}
}
?>