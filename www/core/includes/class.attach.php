<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$GLOBALS['att_type'] = array ();
$GLOBALS['att_type']['IMAGE'] = array (
	'ext'=>array('jpg','jpeg','bmp','gif','png'),
	'title'		=> lang('att_t_img'),
	'titles'	=> lang('att_t_imgs'),
	'icon'=>'jpg'
);
$GLOBALS['att_type']['FVIDEO'] = array (
	'ext'=>array('flv','mp4'),
	'title'		=> lang('att_t_img'),
	'titles'	=> lang('att_t_imgs'),
	'icon'=>'flv'
);
$GLOBALS['att_type']['OFFICE'] = array (
	'ext'=>array('doc'),
	'title'		=> lang('att_t_img'),
	'titles'	=> lang('att_t_imgs'),
	'icon'=>'office'
);
$GLOBALS['att_type']['PDF'] = array (
	'ext'=>array('pdf'),
	'title'		=> lang('att_t_img'),
	'titles'	=> lang('att_t_imgs'),
	'icon'=>'pdf'
);
$GLOBALS['att_type']['FILE'] = array (
	'ext'=>array(),
	'title'		=> lang('att_t_img'),
	'titles'	=> lang('att_t_imgs'),
	'icon'=>'unk'
);

$GLOBALS['att_imgsize'] = array (1,5,10,12,16,32,40,50,60,70,80,100,128,130,140,150,240,256,320,460,768,1024,2048);

class attach
{
	public $id_1;
	public $id_2;

	function init ($id1, $id2)
	{
		$this->id_1 = $id1;
		$this->id_2 = $id2;
	}

	function temp_mode ($force = false)
	{
		if (isset($_COOKIE['att_tmp_'.$this->id_1]) && !$force)
		{
			$this->id_2 = intval($_COOKIE['att_tmp_'.$this->id_1]);
		} else {
			$this->id_2 = -mt_rand();			
		}
		setcookie('att_tmp_'.$this->id_1, $this->id_2, time()+3600, '/', COOKIE_DOMAIN);
	}

	function untemp ($new_id)
	{
		kdb_query ('UPDATE `site_attach_post` SET `id_2`='.$new_id.' WHERE `id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2.' AND `uid`='.user('id'));
	}

	function file_link ($data)
	{
		if (!is_array($data)) $data = kdb_select_one('site_attach_files', '*', $data);
		if (!$data) return;
		return URL.'/file/'.$data['id'].'/'.$data['key'].'/'.rawurlencode($data['file_name']);
	}
	
	function get_cform (&$fg)
	{
		$cnt = kdb_count ('site_attach_post','`id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2);
		
		$tpl = new tpl('att_main');
		$tpl->v('id1', $this->id_1);
		$tpl->v('id2', $this->id_2);
		$tpl->v('cnt', $cnt);
		$tpl = $tpl->get();
		#$fg->add_title('<a href="javascript:toggle_div_hide(\'att_main_'.$this->id_1.'_'.$this->id_2.'\');">Управление файлами</a>');
		$fg->add_input ('raw', '<tr><td class="formgen_input_area" colspan="2" align="center" id="att_main_'.$this->id_1.'_'.$this->id_2.'">'.$tpl.'</td></tr>');

		#$fg->add_input ('raw', '');
	}

	function upload ($file_data)
	{
		if (!@$file_data) return false;
		if (!is_uploaded_file(@$file_data['tmp_name'])) return false;

		# Add file!!
		$kdb_data = array ();
		$kdb_data['file_name']	= $file_data['name'];
		$kdb_data['file_name']	= preg_replace ('/\.+/', '.', $kdb_data['file_name']);
		$kdb_data['file_name']	= preg_replace ('/[^\pL\d,._\- ]/Uuims', ' ', $kdb_data['file_name']);
		$kdb_data['file_name']	= preg_replace ('/\s+/Uuims', ' ', $kdb_data['file_name']);
		$kdb_data['file_name']	= trim ($kdb_data['file_name']);

		$kdb_data['file_size']	= filesize($file_data['tmp_name']);
		$kdb_data['uid']			= user('id');
		$kdb_data['tms_upload']	= time();
		$kdb_data['links_count']	= 1;
		$kdb_data['file_mime']	= @ $file_data['type'];
		$kdb_data['att_type']	= @ $file_data['att_type']?$file_data['att_type']:'ATTACH';
		$kdb_data['att_type2']	= @ $file_data['att_type2'];
		$kdb_data['key']			= md5(md5(mt_rand().time().implode(';',$kdb_data).@$_SERVER['HTTP_USER_AGENT']));

		$file_id = kdb_insert('site_attach_files', $kdb_data);

		if (!copy ($file_data['tmp_name'], ROOT_PATH.'/uploads/att-'.$file_id.'.dat'))
		{
			kdb_query ('DELETE FROM `site_attach_files` WHERE `id`='.$file_id);
			return false;
		}

		# Save data file
		file_put_contents(ROOT_PATH.'/uploads/att-'.$file_id.'.inf', serialize($kdb_data));

		return $file_id;
	}

	function remove_post ()
	{
		kdb_query ('DELETE FROM `site_attach_post` WHERE `id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2);
		attach::recount();
	}

	function remove_by_id ($ids)
	{
		if (!is_array($ids)) $ids = array($ids);
		# Decrease links count
		kdb_query ('UPDATE `site_attach_files` SET `links_count`=`links_count`-1 WHERE `id` IN ('.implode(',', $ids).')');
		attach::recount();
	}

	function recount()
	{
		# Delete old attached (temp) files
		kdb_query ('DELETE FROM `site_attach_post` WHERE `id_2`<0 AND `tms_added`<'.(time()-86400));

		# Recount link's count
		# kdb_query ('UPDATE `site_attach_files` SET `links_count`=(SELECT COUNT(*) FROM `site_attach_post` WHERE `site_attach_post`.`file_id`=`site_attach_files`.`id`) WHERE `id` IN ('.implode($ids).')');
		kdb_query ('UPDATE `site_attach_files` SET `links_count`=(SELECT COUNT(*) FROM `site_attach_post` WHERE `site_attach_post`.`file_id`=`site_attach_files`.`id`) WHERE `att_type`=\'ATTACH\'');

		# Delete attaches without parents
		$data = kdb_select ('site_attach_files','*','`links_count`<=0');
		if ($data)
		{
			for ($x=0; $x<count($data); $x++)
			{
				@ unlink (ROOT_PATH.'/uploads/att-'.$data[$x]['id'].'.dat');
				@ unlink (ROOT_PATH.'/uploads/att-'.$data[$x]['id'].'.inf');
			}
			kdb_query ('DELETE FROM `site_attach_files` WHERE `id` IN ('.implode(',',array_ids($data)).')');
		}
	}

	function list_prev ($file_data)
	{
		$type = attach::get_type($file_data['file_name']);
		if ($type == 'IMAGE')
		{
			return '<img src="'.attach::file_link($file_data).'?size=100x100"/>';
		}
		if ($type == 'FVIDEO')
		{
			return '<img src="'.attach::file_link($file_data).'?size=100x80"/>';
		}

		return '<img src="'.URL.'/tpl/images/attach/'.$GLOBALS['att_type'][$type]['icon'].'.png"/>';
	}

	function get_type ($name)
	{
		$inf = pathinfo(strtolower($name));
		$ext = @$inf['extension'];

		foreach ($GLOBALS['att_type'] as $ct=>$d)
		{
			for ($x=0;$x<count($d['ext']);$x++)
				if ($ext == $d['ext'][$x]) return $ct;
		}

		return 'FILE';
	}

	function get_img_prev ()
	{
		# Get attached files
		$data = kdb_select ('site_attach_files','*','`id` IN (SELECT `file_id` FROM `site_attach_post` WHERE `id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2.')');
		if (!$data) return false;
		$out = array ('cnt'=>0, 'url'=>'');

		for ($x=0; $x<count($data); $x++)
		{
			if ($this->get_type($data[$x]['file_name']) == 'IMAGE')
			{
				if (!$out['url']) $out['url'] = $this->file_link($data[$x]).'?size=100x1000';
				$out['cnt']++;
			}
		}
		if (!$out['cnt']) return false;

		return $out;
	}

	function get_video_prev ()
	{
		# Get attached files
		$data = kdb_select ('site_attach_files','*','`id` IN (SELECT `file_id` FROM `site_attach_post` WHERE `id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2.')');
		if (!$data) return false;
		$out = 0;
		for ($x=0; $x<count($data); $x++)
		{
			if ($this->get_type($data[$x]['file_name']) == 'FVIDEO')
			{
				$out++;
			}
		}
		if (!$out) return false;

		return $out;
	}

	function post_attach ($text)
	{
		$data = kdb_select ('site_attach_files','*','`id` IN (SELECT `file_id` FROM `site_attach_post` WHERE `id_1`=\''.$this->id_1.'\' AND `id_2`='.$this->id_2.')');
		if (!$data) return '';
		
		$data = array_id2key($data);
		
		# Get list of attaches inline in post
		$match = array ();
		if (preg_match_all('"file/([0-9]+)/"Uuims', $text, $m))
		{
			for ($x=0; $x<count($m[1]); $x++)
			{
				if (isset($data[$m[1][$x]]))
				{
					$match[$m[1][$x]] = 1;
				}
			}
		}

		$types = array ();

		foreach ($data as $id=>$at)
		{
			if (isset($match[$id])) continue;
			$type = $this->get_type($at['file_name']);
			if ($type == 'IMAGE')
			{
				$types['image'][] = $at;
				continue;
			}
			if ($type == 'FVIDEO')
			{
				$types['fvideo'][] = $at;
				continue;
			}
			$types['other'][] = $at;
		}
		
		if (!$types) return ''; // No files

		$out = '';

		# Images
		if (@$types['image'])
		{
			$out .= '<div class="attaches_list">';
			$out .= '<a name="attach_img"></a>';
			$out .= '<h3>Фотографии</h3>';
			foreach ($types['image'] as $att)
			{
				$out .= '<a href="'.$this->file_link($att).'" rel="lightbox[roadtrip]"><img src="'.$this->file_link($att).'?size=600x120" alt="" style="margin:3px;vertical-align:middle;" class="attach_img_gal"/></a> ';
			}
			$out .= '</div>';
		}

		# Flash video
		if (@$types['fvideo'])
		{
			$out .= '<div class="attaches_list">';
			$out .= '<a name="attach_video"></a>';
			$out .= '<h3>Видео</h3>';

			$tpl = new tpl ('attach_video');
			$list = '';
			$init = array ();
			foreach ($types['fvideo'] as $att)
			{
				if (!$init) $init = $att;
				$list .= '<table width="100%" cellpadding="0" cellspacing="0"><tr>';
				$list .= '<td width="80" align="center"><img src="'.URL.'/tpl/img/play_sd.png" id="att_video_btn_'.$att['id'].'" style="cursor:pointer;" onclick="play_video('.$att['id'].',\''.$att['key'].'\');" alt="Посмотреть" title="Посмотреть"/></td>';
				$list .= '<td align="left" valign="top">';
				#$list .= '<div class="attach_video_name">'.$att['file_name'].'</div>';
				#$list .= '<div class="attach_video_size">'.format_size($att['file_size']).'</div>';
				$list .= '</td>';
				$list .= '</tr></table>';
			}
			$init['url'] = attach::file_link($init);

			$tpl->v('list', $list);
			$tpl->v('init', $init);
			$out .= $tpl->get();
			$out .= '</div>';
		}

		# Other
		if (@$types['other'])
		{
			$out .= '<div class="attaches_list">';
			$out .= '<h3>Прочие файлы</h3>';
			foreach ($types['other'] as $att)
			{
				$out .= '<table width="100%" cellpadding="1" cellspacing="0"><tr>';
				$out .= '<td width="80" align="center"><a href="'.$this->file_link($att).'" target="_blank">'.$this->list_prev($att).'</a></td>';
				$out .= '<td valign="top" align="left">';
				$out .= '<div><a href="'.$this->file_link($att).'" target="_blank">'.$att['file_name'].'</a></div>';
				$out .= 'Размер: '.format_size($att['file_size']);
				#$out .= ' <img src="'.URL.'/file/'.$att['id'].'/'.$att['file_name'].'?size=120x120" alt=""/></a> ';
				$out .= '<td></tr></table>';
			}
			$out .= '</div>';
		}

		# dbg ($types);
		return $out;
	}
}

?>