<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

class mod_files extends module_template
{
	function display ()
	{
		current_page('files');
		page_title(lang('fl_mylist'),URL.'/files/');
		
		if (!user('logged'))
		{
			return login_req();
		}
		
		$data = kdb_select('upload','*','`uid`='.user('id').' ORDER BY `tms_upload` DESC');

		$u_list = '';
		
		for ($x=0; $x<count($data); $x++)
		{
			$f_title = '';
			
			if ($data[$x]['comment'])
				$f_title = htmlspecialchars ($data[$x]['comment']);
			else {
				# Get files
				$f_list = kdb_select('file',array('file_name'),'`upid`='.$data[$x]['id'].' ORDER BY `id`');
				$f_list_len = 0;
				$f_list_d = array ();
				for ($a=0; $a<count($f_list); $a++)
				{
					$f_list_d[] = '<i>'.htmlspecialchars($f_list[$a]['file_name']).'</i>';
					$f_list_len += mb_strlen($f_list[$a]['file_name'],'UTF-8');
					if ($f_list_len > 50)
						break;
				}
				if (count($f_list_d) < count($f_list))
					$f_list_d[] = '<b>...</b>';
				$f_title = implode(', ',$f_list_d);
			}
			$f_title = trim($f_title);
			if (!$f_title)
				$f_title = sprintf(lang('fld_title_n'),$data[$x]['id']);
			$u_list .= '<tr>';
			$u_list .= '<td align="center">'.$data[$x]['id'].'</td>';
			$u_list .= '<td align="left" class="mf-table-flink"><a href="'.URL.'/f/'.$data[$x]['code'].'/">'.$f_title.'</a></td>';
			$u_list .= '<td align="center">'.date('d.m.Y H:i',$data[$x]['tms_upload']).'</td>';
			$u_list .= '<td align="center">'.time_delete($data[$x]['tms_upload'],$data[$x]['tms_delete']).'</td>';
			$u_list .= '<td align="center">'.format_size($data[$x]['file_size']).'</td>';
			$u_list .= '</tr>';
		}
		
		$tpl = new tpl('myfiles');
		$tpl->v('u_list',$u_list);		
		return $tpl->get();
	}
}
?>