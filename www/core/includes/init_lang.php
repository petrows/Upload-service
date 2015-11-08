<?php

if (!defined('IN_K')) exit ('No Access');

function core_load_lang ($lang_code = false)
{
	$def_lang = @$GLOBALS['config']['default_lang'];
	#default_lang
	if (!$lang_code) $lang_code = $def_lang;
	
	# 1. Load default lang (always!)
	if ($lang_code !== $def_lang)
	{
		$lang = array ();
		require (CORE_PATH.'/lang/'.substr($def_lang, 0, 3).'.php');
		$GLOBALS['lang'] = $lang;
		$GLOBALS['lcode'] = $def_lang;
	}
	
	# Load user-selected lang
	$lang_code = substr(preg_replace('/[^a-z0-9]/','', $lang_code), 0, 3);
	if (!file_exists(CORE_PATH.'/lang/'.$lang_code.'.php'))
		return; # No lang loading :)
	$lang = array ();
	require (CORE_PATH.'/lang/'.$lang_code.'.php');
	$GLOBALS['lang'] = $lang;
	$GLOBALS['lcode'] = $lang_code;
}

function core_load_lang_cc ()
{
	if (isset($GLOBALS['lang']['cc'])) return;
	$GLOBALS['lang']['cc'] = array ();

	if (!file_exists(CORE_PATH.'/lang/'.$GLOBALS['lcode'].'.cc.php'))
	{
		return;
	}
	require_once (CORE_PATH.'/lang/'.$GLOBALS['lcode'].'.cc.php');
}
function core_load_lang_lc ()
{
	if (isset($GLOBALS['lang']['lc'])) return;
	$GLOBALS['lang']['lc'] = array ();

	if (!file_exists(CORE_PATH.'/lang/'.$GLOBALS['lcode'].'.lc.php'))
	{
		return;
	}
	require_once (CORE_PATH.'/lang/'.$GLOBALS['lcode'].'.lc.php');
}

if (isset ($_COOKIE['user_lang']))
{
	core_load_lang ($_COOKIE['user_lang']);
} else {
	core_load_lang ();
}

?>