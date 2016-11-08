<?php

if (!defined('IN_K')) exit ('No Access');

ini_set('log_errors', true);

function __autoload($name)
{
	if (!file_exists(CORE_PATH . '/includes/class.' . $name . '.php'))
		throw new RuntimeException("Class file of $name is not found!");
	require_once CORE_PATH . '/includes/class.' . $name . '.php';
}

function fatal_error($text)
{
	@header("HTTP/1.0 500 Internal Server Error");
	@header("Content-type: text/html");
	
	$text_print = $text;
	
	if (is_object($text) && method_exists($text, 'getMessage')) {
		$text_print = basename($text->getFile()) . ':' . $text->getLine() . ' : ' . $text->getMessage();
		
		if (is_debug() && method_exists($text, 'getTraceAsString')) {
			$text_print .= "\n\n" . $text->getTraceAsString();
		}
	}
	
	echo '<h3>Fatal error!</h3>';
	echo '<pre>' . $text_print . '</pre>';
	exit();
}

set_exception_handler('fatal_error');

function is_debug()
{
	if (preg_match("/^(172|127)\./", $_SERVER['REMOTE_ADDR'])) return true;
	
	return false;
}

function time_offset()
{
	# User?
	if (user('logged')) {
		return intval(user('tmz')) + (SUMMER_TIME ? 1 : 0);
	}
	
	# This is real time zone, no summer time correction!
	if (@$_COOKIE['site_tz']) {
		return intval($_COOKIE['site_tz']);
	}
	
	# Default - return site TZ
	return cfg('site_tz') + (SUMMER_TIME ? 1 : 0);
}

function datel_tms($tms = false)
{
	if (!$tms) $tms = time();
	$tms += (time_offset() * 3600);
	
	return $tms;
}

function datel_quote($str)
{
	$out = '';
	for ($x = 0; $x < mb_strlen($str, 'UTF-8'); $x++) {
		$out .= '\\' . mb_substr($str, $x, 1);
	}
	
	return $out;
}

function datel_date($format, $tms = false)
{
	$tms = datel_tms($tms);
	
	if (strchr($format, 'F')) {
		$format = str_replace('F', datel_quote($GLOBALS['lang'][ 'time_ms_' . gmdate('n', $tms) ]), $format);
	}
	
	return gmdate($format, $tms);
}

function datel_date_str($tms = false, $time = true)
{
	$tms = datel_tms($tms);
	$tms_now = datel_tms();
	
	$day = intval(gmdate('z', $tms));
	$day_now = intval(gmdate('z', $tms_now));
	$dt = '';
	if ($tms_now - $tms < 172800) {
		if ($day == $day_now) {
			$dt = '<i>' . lang('time_today') . '</i>';
			if ($time) $dt .= ',';
		} else if (($day_now == 0 && $day == 365) || ($day_now - $day == 1)) {
			$dt = '<i>' . lang('time_yesterday') . '</i>';
			if ($time) $dt .= ',';
		}
	}
	if (!$dt) $dt = gmdate('j', $tms) . ' ' . $GLOBALS['lang'][ 'time_ms_' . gmdate('n', $tms) ] . ' ' . gmdate('Y', $tms);
	if ($time) $dt .= ' ' . gmdate('H:i', $tms);
	
	return $dt;
}

function datel($format, $tms = false)
{
	return datel_date($format, $tms);
}

function cfg($name)
{
	if (!isset ($GLOBALS ['config'] [ $name ])) {
		trigger_error('core::cfg : there is no such cfg option "' . $name . '"!', E_USER_WARNING);
		
		return false;
	}
	
	return $GLOBALS ['config'] [ $name ];
}

function lang($var)
{
	if (!isset ($GLOBALS ['lang'] [ $var ]))
		return 'Lang: ' . $var;
	
	return $GLOBALS ['lang'] [ $var ];
}

function text_unk($text = false, $misstext = false)
{
	if (!$text) return '<span class="unk_text">' . ($misstext ? $misstext : lang('unknown')) . '</span>';
	
	return $text;
}

function country_title($cntr)
{
	if ($cntr == 'XX') {
		return text_unk(false, lang('cc_all'));
	}
	if (!isset($GLOBALS['lang']['cc'][ strtoupper($cntr) ])) {
		return '<img src="' . URL . '/tpl/images/cc/xx.gif" style="vertical-align:middle"/> ' . text_unk(false);
	}
	
	return '<img src="' . URL . '/tpl/images/cc/' . strtolower($cntr) . '.png" style="vertical-align:middle"/> ' . $GLOBALS['lang']['cc'][ strtoupper($cntr) ];
}

function country_title_s($cntr)
{
	if ($cntr == 'XX') {
		return text_unk(false, lang('all'));
	}
	if (!isset($GLOBALS['lang']['cc'][ strtoupper($cntr) ])) {
		return '<img src="' . URL . '/tpl/images/cc/xx.gif" style="vertical-align:middle" title="Unknown"/>';
	}
	
	return '<img src="' . URL . '/tpl/images/cc/' . strtolower($cntr) . '.png" style="vertical-align:middle" title="' . $GLOBALS['lang']['cc'][ strtoupper($cntr) ] . '"/> ' . $cntr;
}

function input($index, $test_var = false)
{
	if (isset ($GLOBALS ['input'] [ $index ])) {
		if (!$test_var)
			return $GLOBALS ['input'] [ $index ];
		if ($GLOBALS ['input'] [ $index ] == $test_var)
			return true;
	}
	
	return false;
}

function dbg()
{
	$arg = func_get_args();
	echo '<div style="padding:5px;margin:5px;border:1px dotted #333;">' . "\n";
	$out = array();
	foreach ($arg as $k => $v) {
		$out[] = '<pre>' . htmlspecialchars(print_r($v, true)) . '</pre>';
	}
	echo implode("\n<hr/>\n", $out);
	echo '</div>';
}

function string_get($params = false)
{
	$data = $_GET;
	if ($params)
		$data = array_merge($data, $params);
	$out = array();
	foreach ($data as $k => $v) {
		$out[] = $k . '=' . rawurlencode($v);
	}
	
	return '?' . implode('&', $out);
}

function pages_split($all_count, $per_page = 20, $page_var = 'page')
{
	$page = isset($_GET[ $page_var ]) ? intval($_GET[ $page_var ]) : 1;
	if ($page < 1) $page = 1;
	$pages_count = ceil($all_count / $per_page);
	if (($page < 1) || ($page > $pages_count)) $page = 1;
	
	$start_c = ($per_page * ($page - 1));
	$end_c = $start_c + $per_page;
	
	$out['mysql_limit'] = "LIMIT " . $start_c . "," . $per_page;
	$out['start_c'] = $start_c;
	$out['end_c'] = $start_c + $per_page;
	$out['pages_text'] = array();
	
	for ($x = 0; $x < $pages_count; $x++) {
		$pn = $x + 1;
		if ($page == $pn) {
			$out['pages_text'][] = '<b style="color:red;">' . $pn . '</b>';
		} else {
			$out['pages_text'][] = '<a href="' . string_get(array($page_var => $pn)) . '">' . $pn . '</a>';
		}
	}
	
	if (count($out['pages_text']) == 1)
		$out['pages_text'] = '<small>' . lang('one_page') . '</small>';
	else
		$out['pages_text'] = implode(' ', $out['pages_text']);
	
	$out['pages_text'] = '<div class="pagebar">' . $out['pages_text'] . '</div>';
	
	return $out;
}

function time_mulipier($type)
{
	$mult = 86400;
	if ($type == 'W') {
		$mult = 604800;
	}
	if ($type == 'M') {
		$mult = 2592000;
	}
	if ($type == 'Y') {
		$mult = 31536000;
	}
	
	return $mult;
}

function format_size($size, $arr = false)
{
	$units = '';
	
	$size_m = ($size < 0);
	$size = abs($size);
	
	if ($size <= 1024) {
		$units = "b";
	} else {
		if ($size < 1048576) # 1024^2
		{
			$units = "Kb";
			$size = $size / 1024;
		} else {
			if ($size < 1073741824) # 1024^3
			{
				$units = "Mb";
				$size = $size / (1048576);
			} else {
				if ($size < 1099511627776) # 1024^4
				{
					$units = "GB";
					$size = $size / (1073741824);
				} else {
					if ($size < 1125899906842624) # 1024^5
					{
						$units = "Tb";
						$size = $size / (1099511627776);
					} else {
						$units = "Eb";
						$size = $size / (1125899906842624); # 1024^6
					}
				}
			}
		}
	};
	
	if ($size_m) $size = -$size;
	
	if ($arr)
		return array(round($size, 2), $units);
	else
		return round($size, 2) . ' ' . $units;
}

function deformat_size($size)
{
	if (is_numeric($size)) return intval($size);
	$index = strtolower(substr($size, -1, 1));
	$size = floatval(substr($size, 0, -1));
	
	if ($index == 'k') return $size * 1024;
	if ($index == 'm') return $size * 1048576;
	if ($index == 'g') return $size * 1073741824;
	if ($index == 't') return $size * 1099511627776;
	if ($index == 'e') return $size * 1125899906842624;
	
	return $size;
}

function upl_max_size()
{
	$sz = array();
	$sz[] = deformat_size(ini_get('upload_max_filesize'));
	$sz[] = deformat_size(ini_get('memory_limit'));
	$sz[] = deformat_size(ini_get('post_max_size'));
	$sz = min($sz);
	
	return $sz;
}

function diff_suff($tms, $type)
{
	static $words = array(
		array('([567890]|([1][0-9])|20)$', 'минут', 'часов'),
		array('1$', 'минута', 'час'),
		array('[2-4]$', 'минуты', 'часа'),
	);
	
	$fn = false;
	for ($n = 0; $n < count($words); $n++) {
		if (preg_match('/' . $words[ $n ][0] . '/', (string)$tms))
			return $tms . ' ' . $words[ $n ][ $type ] . ' назад';
	}
	
	return $tms . ' ' . $words[0][ $type ];
}

function time_diff($tms)
{
	
	$diff = time() - $tms;
	if ($diff < 300) {
		return 'Только что';
	}
	if ($diff < 3600) {
		return diff_suff(ceil($diff / 60), 1);;
	}
	if ($diff < 36000) {
		return diff_suff(ceil($diff / 3600), 2);;
	}
	
	return datel('d.m.Y H:i', $tms);
}

function uniq_string($len = 8)
{
	$string = '';
	$chars_list = array(
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
		'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
		'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	);
	for ($x = 0; $x < $len; $x++) {
		$string .= $chars_list[ mt_rand(0, count($chars_list) - 1) ];
	}
	
	return $string;
}

function format_num($val, $dec = 0)
{
	return number_format($val, $dec, '.', ' ');
}

function js_unescape_rep_c($i)
{
	return mb_convert_encoding(@pack('H*', $i[1]), 'UTF-8', 'UTF-16');
}

function js_unescape($str)
{
	$str = preg_replace_callback('/%u([0-9-a-f]{2,4})/i', 'js_unescape_rep_c', $str);
	
	return $str;
}

function js_escape($str)
{
	$str = mb_convert_encoding($str, 'UTF-16', 'UTF-8');
	$out = '';
	for ($i = 0; $i < mb_strlen($str, 'UTF-16'); $i++) {
		$out .= '%u' . bin2hex(mb_substr($str, $i, 1, 'UTF-16'));
	}
	
	return $out;
}

function redirect_msg($url, $text)
{
	$tpl = new ltpl ('redirect_msg');
	$tpl->v('msg', $text);
	$tpl->v('red_url', $url);
	echo $tpl->get();
	exit ();
}

function global_error($text)
{
	echo "<html><head><title>Error!</title><body><code>$text</code></body></html>";
	exit ();
}

function core_errors()
{
	return empty($GLOBALS['core']->error) ? false : true;
}

function core_error($text)
{
	$GLOBALS['core']->error[] = $text;
}

function core_error_lng($var)
{
	core_error(lang($var));
}

function core_error_404()
{
	site_title(lang('404_e_t'));
	@ header('HTTP/1.1 404 Not Found');
	$tpl = new ltpl ('ge_404');
	$GLOBALS['core']->global_msg = $tpl->get();
	for ($x = 0; $x < 100; $x++)
		echo '                                                                  ';
	
	return $tpl->get();
	exit();
}

function core_error_403()
{
	site_title(lang('403_e_t'));
	$tpl = new ltpl ('ge_403');
	$GLOBALS['core']->global_msg = $tpl->get();
}

function core_error_custom($text)
{
	$GLOBALS['core']->global_msg = $text;
}

function core_error_login()
{
	site_title(lang('403_e_t'));
	$tpl = new ltpl ('ge_403');
	$GLOBALS['core']->global_msg = $tpl->get();
}

function core_info($text, $title = false)
{
	$tpl = new ltpl ('gm_200');
	if (!$title) $title = lang('info');
	$tpl->v('title', $title);
	$tpl->v('text', $text);
	$GLOBALS['core']->global_msg = $tpl->get();
}

function page_title($text, $link = false)
{
	if ($link)
		$text = '<a href="' . $link . '">' . $text . '</a>';
	
	$GLOBALS['core']->page_title[] = $text;
}

function site_title($text)
{
	$GLOBALS['core']->site_title = $text;
}

function current_page($page)
{
	$GLOBALS['core']->current_page = $page;
}

function sort_field($sv = '', $n = 0, $title = '', $def_sort = '1')
{
	if (@$_GET[ $sv . '_sort_by' ] == $n) {
		if (intval(@$_GET[ $sv . '_sort_order' ]) == 1) {
			return '&uarr;&nbsp;<a href="' . string_get(array($sv . '_sort_by' => $n, $sv . '_sort_order' => '0')) . '" class="tablegen_th_a">' . $title . '</a>';
		} else {
			#&darr;
			return '&darr;&nbsp;<a href="' . string_get(array($sv . '_sort_by' => $n, $sv . '_sort_order' => '1')) . '" class="tablegen_th_a">' . $title . '</a>';
		}
	} else {
		return '<a href="' . string_get(array($sv . '_sort_by' => $n, $sv . '_sort_order' => $def_sort)) . '" class="tablegen_th_a">' . $title . '</a>';
	}
}

function table_sort_field($title, $name, $def_sort = 'A', $sv = 's')
{
	if (@$_GET[ $sv . '_sf' ] == $name) {
		if (strtoupper(@$_GET[ $sv . '_so' ]) == 'D') {
			return '&uarr;&nbsp;<a href="' . string_get(array($sv . '_sf' => $name, $sv . '_so' => 'A')) . '" class="tablegen_th_a">' . $title . '</a>';
		} else {
			return '&darr;&nbsp;<a href="' . string_get(array($sv . '_sf' => $name, $sv . '_so' => 'D')) . '" class="tablegen_th_a">' . $title . '</a>';
		}
	} else {
		return '<a href="' . string_get(array($sv . '_sf' => $name, $sv . '_so' => $def_sort)) . '" class="tablegen_th_a">' . $title . '</a>';
	}
}

function table_sort_field_callback($a, $b)
{
	if (!@$GLOBALS['sort_sv']) $GLOBALS['sort_sv'] = 's';
	$r = strnatcasecmp(@$a[ @$_GET[ $GLOBALS['sort_sv'] . '_sf' ] ], @$b[ @$_GET[ $GLOBALS['sort_sv'] . '_sf' ] ]);
	
	return (@$_GET[ $GLOBALS['sort_sv'] . '_so' ] == 'D' ? -$r : $r);
}

function array_id($id, $arr, $id_key = 'id')
{
	for ($x = 0; $x < count($arr); $x++) {
		if (@$arr[ $x ][ $id_key ] == $id)
			return $arr[ $x ];
	}
	
	return false;
}

function array_idm($id, $arr, $id_key = 'id')
{
	$out = array();
	for ($x = 0; $x < count($arr); $x++) {
		if (@$arr[ $x ][ $id_key ] == $id)
			$out[] = $arr[ $x ];
	}
	
	return $out;
}

function array_id2key($arr, $id_key = 'id')
{
	$tmp = array();
	for ($x = 0; $x < count($arr); $x++) {
		if (!isset($arr[ $x ][ $id_key ])) continue;
		$tmp[ $arr[ $x ][ $id_key ] ] = $arr[ $x ];
	}
	
	return $tmp;
}

function array_ids($arr, $id = 'id')
{
	$out = array();
	for ($x = 0; $x < count($arr); $x++) {
		if (!isset($arr[ $x ][ $id ])) continue;
		$out[] = $arr[ $x ][ $id ];
	}
	
	return $out;
}

function resize_image($file, $max_x, $max_y, $func = false)
{
	$s = @getimagesize($file);
	$format = strtolower(substr($s ['mime'], strpos($s ['mime'], '/') + 1));
	$icfunc = "imagecreatefrom" . $format;
	
	if (!function_exists($icfunc)) {
		return $file;
	}
	
	if (!$func)
		$func = $format;
	
	$source = $icfunc ($file);
	
	$ratio_x = 1;
	$ratio_y = 1;
	
	if ($s [0] <= $max_x && $s [1] <= $max_y)
		return $file;
	
	$ratio_x = $max_x / $s [0];
	$ratio_y = $max_y / $s [1];
	
	$ratio = min($ratio_x, $ratio_y);
	
	$new_size_x = floor($s [0] * $ratio);
	$new_size_y = floor($s [1] * $ratio);
	
	$resource = imagecreatetruecolor($new_size_x, $new_size_y);
	imagesavealpha($resource, true);
	imagealphablending($source, true);
	
	if ($format == 'gif' && $func == 'gif') {
		$colorcount = imagecolorstotal($source);
		imagetruecolortopalette($resource, true, $colorcount);
		imagepalettecopy($resource, $source);
		$transparentcolor = imagecolortransparent($source);
		# imagefill($resource,0,0,$transparentcolor);
		imagecolortransparent($resource, $transparentcolor);
	} else {
		imagefill($resource, 0, 0, imagecolorallocatealpha($source, 0, 0, 0, 127));
	}
	
	if (imagecopyresampled($resource, $source, 0, 0, 0, 0, $new_size_x, $new_size_y, $s [0], $s [1])) {
		$new_name = tempnam('/tmp', 'ktt');
		if ($func == 'gif' && function_exists('imagegif')) {
			imagegif($resource, $new_name);
		} else if ($func == 'png' && function_exists('imagepng')) {
			
			imagepng($resource, $new_name);
		} else {
			imagejpeg($resource, $new_name, 80);
		}
		
		return $new_name;
	} else {
		return $file;
	}
}

function remove_html($text)
{
	$text = preg_replace("'<[\/\!]*?[^<>]*?>'Usimu", " ", $text);
	$text = preg_replace('/\s+/Uuims', ' ', $text);
	
	return $text;
}

function short_text_html($text, $minchar = 100, $minp = 3)
{
	$text = preg_replace("'<[\/\!]*?img[^<>]*?>'Usimu", " ", $text);
	$text = preg_replace("'<object[^<>]*?>.*</object[^<>]*?>'Usimu", " ", $text);
	$text = preg_replace("'<p[^<>]*?>(\s|&nbsp;)*</p[^<>]*?>'Usimu", " ", $text);
	$data = explode('</p>', $text);
	if (!$data) return '';
	# dbg($data);
	$len = 0;
	$out = '';
	for ($x = 0; $x < count($data); $x++) {
		$len += mb_strlen(remove_html($data[ $x ]), 'UTF-8');
		$out .= $data[ $x ] . '</p>';
		if ($len >= $minchar) break;
		if ($x >= $minp - 1) break;
	}
	
	return $out;
}

function short_text($text, $minchar = 100, $minp = 3)
{
	$data = explode('.', $text);
	if (!$data) return '';
	
	$len = 0;
	$out = '';
	for ($x = 0; $x < count($data); $x++) {
		$len += mb_strlen($data[ $x ], 'UTF-8');
		$out .= $data[ $x ] . '.';
		if ($len >= $minchar) break;
		if ($x >= $minp - 1) break;
	}
	
	return $out;
}

function init_auth()
{
	if (!@cfg('auth_type')) fatal_error('Invalid auth type specified');
	if (!file_exists(CORE_PATH . '/auth/' . cfg('auth_type') . '.php')) fatal_error('Invalid auth type specified');
	require CORE_PATH . '/auth/' . cfg('auth_type') . '.php';
	$GLOBALS['auth'] = new auth ();
	$GLOBALS['auth']->init();
}

function send_mail_enc($text)
{
	return "=?utf-8?b?" . base64_encode($text) . "?=";
}

function send_mail($toname, $to, $subj, $data, $type = 'text/plain')
{
	$grname = sprintf(lang('mail_greetings'), $toname);
	$data = str_replace('{GREET}', $grname, $data);
	
	if (cfg('mail_t') == 'php') {
		$headers = array();
		# $headers[] = 'MIME-Version: 1.0';
		$headers[] = 'Content-type: ' . $type . '; charset=UTF-8';
		$headers[] = 'From: ' . $GLOBALS['siteconfig']['site_title'] . ' <' . cfg('mail') . '>';
		$headers = implode("\r\n", $headers) . "\r\n";
		$to = $toname . ' <' . $to . '>';
		mail($to, $subj, $data, $headers);
		
		return true;
	}
	
	if (cfg('mail_t') == 'gmail') {
		require_once CORE_PATH . '/php-mailer/class.phpmailer.php';
		$mail = new PHPMailer();
		$mail->IsSMTP();
		$mail->SMTPAuth = true;                  // enable SMTP authentication
		$mail->SMTPSecure = "ssl";                 // sets the prefix to the servier
		$mail->Host = "smtp.gmail.com";      // sets GMAIL as the SMTP server
		$mail->Port = 465;                   // set the SMTP port for the GMAIL server
		
		$mail->Username = cfg('mail_smtp_user');  // GMAIL username
		$mail->Password = cfg('mail_smtp_pass');  // GMAIL password
		
		$mail->From = cfg('mail');
		$mail->FromName = send_mail_enc(lang('site_title_none'));
		
		$mail->Subject = send_mail_enc($subj);
		
		if ($type == 'text/plain') {
			// Plain text
			$mail->Body = $data;
			// $mail->WordWrap = 50;
		} else {
			// HTML
			$mail->MsgHTML($data);
			$mail->IsHTML(true);
		}
		
		// TO
		$mail->AddAddress($to);
		$res = $mail->Send();
		
		#dbg ($mail->ErrorInfo);
		return $res;
	}
}

$GLOBALS['vote_color'] = 0;

function vote_color()
{
	$colors = array('#666600', '#6633CC', '#FF6600', '#996633', '#666699', '#339966');
	if (!isset($colors[ $GLOBALS['vote_color'] ])) $GLOBALS['vote_color'] = 0;
	$ret = $colors[ $GLOBALS['vote_color'] ];
	$GLOBALS['vote_color']++;
	
	return $ret;
	
}

function show_vote($id)
{
	$id = intval($id);
	$data = db_select_one('site_votes', '*', $id);
	if (!$data) return 'Опрос не найден';
	$ans = @unserialize($data['data']);
	
	# Voting?
	if ($data['is_active'] == 'Y' && user('logged') && isset($_POST['sub_vote']) && !db_select('site_votes_voters', array('id'), '`id`=' . $id . ' AND `uid`=' . user('id'))) {
		# Voting!
		if ($data['type'] == 'S') {
			if (isset($ans[ @$_POST['vote_ans'] ]))
				$ans[ @$_POST['vote_ans'] ]['a']++;
		} else {
			for ($x = 0; $x < count($ans); $x++) {
				if (in_array($x, @$_POST['vote_ans']))
					$ans[ $x ]['a']++;
			}
		}
		
		db_update_by_id('site_votes', $id, array('data' => serialize($ans)));
		db_insert('site_votes_voters', array('id' => $id, 'uid' => user('id'), 'tms' => time()));
		redirect_msg(URL . '/votes/' . $id . '/', 'Спасибо, ваш голос принят!');
		exit();
	}
	
	
	# Check - resuilts?
	$out = '';
	$bot = '';
	$is_res = false;
	if ($data['is_active'] != 'Y' || !user('logged') || isset($_GET['vote_resuilts']) || db_select('site_votes_voters', array('id'), '`id`=' . $id . ' AND `uid`=' . user('id'))) {
		$is_res = true;
	}
	$tpl = new ltpl ('vote_area');
	$tpl->v('title', $data['title']);
	if ($is_res) {
		$GLOBALS['vote_color'] = 0;
		$all = 0;
		for ($x = 0; $x < count($ans); $x++) {
			$all += $ans[ $x ]['a'];
		}
		# Show resuilts
		for ($x = 0; $x < count($ans); $x++) {
			$pers = @ round(($ans[ $x ]['a'] / $all) * 100);
			$out .= '<tr>';
			$out .= '<td width="30" align="center">' . ($x + 1) . '.</td>';
			$out .= '<td align="left">' . htmlspecialchars($ans[ $x ]['t']) . '</td>';
			#$out .= '<td width="30" align="left">'.intval($ans[$x]['a']).'</td>';
			$out .= '<td width="30" align="left">' . $pers . '%</td>';
			$out .= '</tr>';
			
			$pers = @ round(($ans[ $x ]['a'] / $all) * 100);
			if (!$pers) $pers = 1;
			
			$out .= '<tr>';
			$out .= '<td>&nbsp;</td>';
			$out .= '<td align="left" colspan="2"><table width="100%"><tr><td width="' . $pers . '%" style="background-color:' . vote_color() . ';padding:5px;"><img src="' . URL . '/tpl/images/spacer.gif" alt=""/></td><td><img src="' . URL . '/tpl/images/spacer.gif" alt=""/></td></tr></table></td>';
			$out .= '</tr>';
		}
		
		if ($data['is_active'] != 'Y') {
			$bot = 'Опрос уже завершен';
		} elseif (!user('logged')) {
			$bot = 'Гости не могут голосовать';
		} elseif (db_select('site_votes_voters', array('id'), '`id`=' . $id . ' AND `uid`=' . user('id'))) {
			$bot = 'Вы уже отдали свой голос';
		} else {
			$bot = '<input type="submit" value="Голосовать"/>';
		}
		
		#$bot .= '<input type="submit" value="Голосовать"/>';
	} else {
		# Show form
		$idt = mt_rand();
		for ($x = 0; $x < count($ans); $x++) {
			if ($data['type'] == 'S') {
				$ch = '<input type="radio" name="vote_ans" value="' . $x . '" id="vote_' . $idt . '_' . $x . '"/>';
			} else {
				$ch = '<input type="checkbox" name="vote_ans[]" value="' . $x . '" id="vote_' . $idt . '_' . $x . '"/>';
			}
			$out .= '<tr>';
			$out .= '<td width="15" align="center">' . $ch . '</td>';
			$out .= '<td align="left"><label for="vote_' . $idt . '_' . $x . '">' . htmlspecialchars($ans[ $x ]['t']) . '</label></td>';
			$out .= '</tr>';
		}
		
		$bot .= '<input type="submit" name="sub_vote" value="Голосовать"/> <input type="button" value="Результаты" onclick="document.location.href=\'' . URL . '/votes/' . $id . '/?vote_resuilts=1\';"/>';
	}
	$tpl->v('id', $id);
	$tpl->v('data', $out);
	$tpl->v('is_res', $is_res);
	$tpl->v('bot', $bot);
	
	return $tpl->get();
}

function js_enc($data)
{
	# generate key
	$key = strtolower(uniq_string(mt_rand(20, 100)));
	$data = mb_convert_encoding($data, 'UTF-16', 'UTF-8');
	$data_out = array();
	
	for ($x = 0, $n = 0; $x < mb_strlen($data, 'UTF-16'); $x++, $n++) {
		$char = mb_substr($data, $x, 1, 'UTF-16');
		$char = intval(bin2hex($char), 16);
		
		# Get offset
		if ($n >= strlen($key)) $n = 0;
		
		$char = $char >> ($key[ $n ]);
		$data_out[] = $char;
	}
	
	$a = '<noscript><div style="padding:10px;text-align:center;color:red;">Вы должны включить JavaScript для правильной работы функций сайта!</div></noscript>';
	$a .= '<script type="text/javascript">sc(\'' . $key . '\',[' . implode(',', $data_out) . ']);</script>';
	
	return $a;
}

function sr_menu_cascade_n($name)
{
	$data = ldb_select_one('page', '*', $name, 'name');
	
	if (!$data) return '';
	
	$out = '<li' . sr_menu_current('page-' . $name) . '><span class="s5_outer_active"><span class="s5_outer"><a class="active" id="tempID' . mt_rand() . '" href="' . URL . '/' . $data['name'] . '/">' . $data['title'] . '</a></span></span>' . "\n";
	
	$data_root = ldb_select('page', '*', '`root_id`=' . $data['id'] . ' ORDER BY `so`');
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_cascade_s($data)
{
	# Has sub-dirs?
	$data_root = ldb_select('page', '*', '`root_id`=' . $data['id'] . ' ORDER BY `so`');
	
	$out = '<li class="noback"><span><span><a class="' . ($data_root ? 'parent' : 'sub') . '" href="' . URL . '/' . $data['name'] . '/">' . $data['title'] . '</a></span></span>' . "\n";
	
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_personal_cascade_n()
{
	$out = '<li' . sr_menu_current('personal') . '><span class="s5_outer_active"><span class="s5_outer"><a class="active" id="tempID' . mt_rand() . '" href="' . URL . '/personal/">Члены Совета</a></span></span>' . "\n";
	
	$data_root = ldb_select('personal', '*', '`root_id`=0 AND `type`=\'D\' ORDER BY `so`');
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_personal_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_personal_cascade_s($data)
{
	# Has sub-dirs?
	$data_root = ldb_select('personal', '*', '`root_id`=' . $data['id'] . ' AND `type`=\'D\' ORDER BY `so`');
	
	$out = '<li class="noback"><span><span><a class="' . ($data_root ? 'parent' : 'sub') . '" href="' . URL . '/personal/' . $data['id'] . '/">' . $data['name'] . '</a></span></span>' . "\n";
	
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_personal_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_universities_cascade_n()
{
	$out = '<li' . sr_menu_current('universities') . '><span class="s5_outer_active"><span class="s5_outer"><a class="active" id="tempID' . mt_rand() . '" href="' . URL . '/universities/">ВУЗы</a></span></span>' . "\n";
	
	$data_root = ldb_select('universities', '*', '`root_id`=0 AND `type`=\'D\' ORDER BY `so`');
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_universities_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_universities_cascade_s($data)
{
	# Has sub-dirs?
	$data_root = ldb_select('universities', '*', '`root_id`=' . $data['id'] . ' AND `type`=\'D\' ORDER BY `so`');
	
	$out = '<li class="noback"><span><span><a class="' . ($data_root ? 'parent' : 'sub') . '" href="' . URL . '/universities/' . $data['id'] . '/">' . $data['name'] . '</a></span></span>' . "\n";
	
	if ($data_root) {
		$out .= '<ul onmouseover="check_id()">' . "\n";
		foreach ($data_root as $el)
			$out .= sr_menu_universities_cascade_s($el);
		$out .= '</ul>' . "\n";
	}
	$out .= '</li>' . "\n";
	
	return $out;
}

function sr_menu_current($name)
{
	if ($GLOBALS['core']->current_page == $name)
		return ' class="active"';
	
	return '';
}

?>