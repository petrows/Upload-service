<?php
define ('IN_K', true);
define ('ROOT_PATH', dirname(__FILE__));
define ('CORE_PATH', ROOT_PATH.'/core');

require CORE_PATH.'/includes/func.main.php';
require CORE_PATH.'/includes/init_rewrite.php';
require CORE_PATH.'/includes/class.attach.php';

function att_404 ()
{
	@header ('HTTP/1.1 404 Not Found');
	exit ('404 - File is not found');
}

function prev_size_c ($size)
{
	$size = intval ($size);
	if (!$size) return false;
	if (in_array($size,$GLOBALS['att_imgsize'],true)) return $size;
	if ($size>1024) return 1024;
	return round($size/50)*50;
}

function get_prev ($id, $size)
{
	$size = explode ('x', strtolower($size));
	$size[0] = prev_size_c(@$size[0]);
	$size[1] = prev_size_c(@$size[1]);
	if (!$size[1] || !$size[0]) return false;
	
	if (file_exists(ROOT_PATH.'/tmp/attach_thumb/att-'.$id.'-'.$size[0].'-'.$size[1].'.dat'))
		return ROOT_PATH.'/tmp/attach_thumb/att-'.$id.'-'.$size[0].'-'.$size[1].'.dat';
	
	$res = resize_image (ROOT_PATH.'/uploads/att-'.$id.'.dat', $size[0],$size[1]);
	@ copy ($res, ROOT_PATH.'/tmp/attach_thumb/att-'.$id.'-'.$size[0].'-'.$size[1].'.dat');
	return $res;
}

function get_video_prev ($id, $size)
{
	$size = explode ('x', strtolower($size));
	$size[0] = prev_size_c(@$size[0]);
	$size[1] = prev_size_c(@$size[1]);
	if (!$size[1] || !$size[0]) return false;

	$pf = ROOT_PATH.'/tmp/attach_thumb/att-'.$id.'-'.$size[0].'-'.$size[1].'.jpg';

	if (file_exists($pf))
		return $pf;

	$pm = ROOT_PATH.'/tmp/attach_thumb/att-'.$id.'-video.jpg';

	# Exists master-copy?
	if (!file_exists($pm))
	{
		$r = array ();
		exec('/usr/local/bin/ffmpeg -i '.ROOT_PATH.'/uploads/att-'.$id.'.dat -an -ss 5 -r 1 -vframes 1 -s 640x480 -y -f mjpeg '.$pm, $r);
	}

	if (!file_exists($pm))
		return $pm;
	
	$res = resize_image ($pm, $size[0],$size[1]);
	@ copy ($res, $pf);
	return $res;
}

$id 	= intval(@$GLOBALS['input'][0]);
$key	= preg_replace('/[^a-f0-9]/', '', @$GLOBALS['input'][1]);
$name	= @$GLOBALS['input'][2];
#if (!$name) $name = 'file.dat';

#if (!$name) exit();

if (!$id || !$name) att_404();

if (!file_exists(ROOT_PATH.'/uploads/att-'.$id.'.dat')) return att_404();

$data_l = ROOT_PATH.'/uploads/att-'.$id.'.dat';
$data = @ unserialize(file_get_contents(ROOT_PATH.'/uploads/att-'.$id.'.inf'));
if (!$data) att_404();

# if ($name != mb_strtolower($data['file_name'],'UTF-8')) att_404();
if ($key != $data['key']) att_404();

$cache = false;
if (@$_SERVER['HTTP_IF_MODIFIED_SINCE'] || @$_SERVER['HTTP_IF_NONE_MATCH'])
{
	@header ('HTTP/1.1 304 Not Modified');
	$cache = true;
}

$mime = $data['file_mime'];

# thumb requested?
if (@$_GET['size'] && attach::get_type($data['file_name']) == 'IMAGE')
{
	$res = get_prev($id, $_GET['size']);
	if ($res)
	{
		#$mime = 'image/png';
		$data_l = $res;
	}
}
if (@$_GET['size'] && attach::get_type($data['file_name']) == 'FVIDEO')
{
	$res = get_video_prev($id, $_GET['size']);
	#exit ();
	if ($res)
	{
		$mime = 'image/jpeg';
		$data_l = $res;
	}
}

if ($mime) @header ('Content-Type: '.$mime);
else @header ('Content-Type: application/x-force-download');

#@header ('Last-Modified: Fri, 02 May 2008 00:00:00 GMT');
header('Last-Modified: ' . gmdate('D, d M Y H:i:s', 880000) . ' GMT'); 
header('Expires: ' . gmdate('D, d M Y H:i:s', time()+880000) . ' GMT'); 
@header ('Cache-Control: max-age=880000');
#@header ('Etag: "'.md5($id).'"');
@header ('Pragma:');

if ($cache) exit ();

$f = fopen ($data_l, 'r');
header ('Content-Length: '.@filesize($data_l));
while (!feof($f))
{
	echo fgets($f, 1024);
}
fclose($f);
?>