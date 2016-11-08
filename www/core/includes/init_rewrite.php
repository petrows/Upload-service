<?php

if (!defined('IN_K')) exit ('No Access');

if (!@$_SERVER["REQUEST_SCHEME"]) {
	$_SERVER["REQUEST_SCHEME"] = 'http';
	if (@$_SERVER["HTTPS"]) {
		$_SERVER["REQUEST_SCHEME"] = 'https';
	}
}

$our_url = $_SERVER["REQUEST_SCHEME"] . "://" . $_SERVER['HTTP_HOST'] . htmlspecialchars(rtrim(dirname($_SERVER['PHP_SELF']), '/\\'));

if (!defined('URL')) {	
	define ('URL',$our_url);
}

if (!defined('SITE_URL_ABS')) {
	define ('SITE_URL_ABS',$our_url);
}
if (!defined('SITE_URL_SCRIPT')) {
	define ('SITE_URL_SCRIPT',$our_url);
}

# Cookie domain
$cookie_domain = $_SERVER['HTTP_HOST'];
$cookie_domain = preg_replace ('/^www\./', '', $cookie_domain);
$cookie_domain = '.'.$cookie_domain;
define ('COOKIE_DOMAIN', $cookie_domain);

# Current URL
define ('URL_CURRENT', 'http://'.$_SERVER['HTTP_HOST'].htmlspecialchars($_SERVER['REQUEST_URI']));

# Magic_quotes
function strip_mc ($var)
{
	if (is_array($var))
	{
		foreach ($var as $k=>$v)
		{
			$var[$k] = strip_mc ($v);
		}
	} else {
		$var = stripslashes ($var);
	}
	return $var;
}

if (get_magic_quotes_gpc())
{
	$_POST 	= strip_mc ($_POST);
	$_GET 	= strip_mc ($_GET);
	$_COOKIE= strip_mc ($_COOKIE);
}

$GLOBALS['lang'] = array ();
# $GLOBALS['user'] = array ();

function init_rewrite()
{
	$params = array ();
	$GLOBALS['input'] = array ();
	if (! isset($_GET ['url']))
		return;
		
	#if (strrchr($_GET ['url'], 0)!==false) $_GET ['url'] = '';

	$_GET ['url'] = trim ( $_GET ['url'], '/' );
	$_GET ['url'] = preg_replace ( "/[^\pL\d,._\- \/]/Uuims", "", $_GET ['url'] );
	$_GET ['url'] = preg_replace ( "/\.+/", ".", $_GET ['url'] );
	if ($_GET ['url'] == '')
	{
		unset ( $_GET ['url'] );
		return;
	}

	$_GET ['url'] = mb_strtolower($_GET['url'], 'UTF-8');
	$GLOBALS['input'] = explode ('/', $_GET['url']);
	$_GET = array ();
	
	$url = parse_url ( $_SERVER ['REQUEST_URI'] );
	if (! isset ( $url ['query'] ))
		return;
	if (strlen ( $url ['query'] ) > 2048) {
		return;
	}
	
	parse_str($url['query'],$params);
			
	foreach ( $params as $k => $v ) 
	{
		$params [$k] = addslashes ($v);
	}

	$_GET = $params;
}

init_rewrite ();

?>
