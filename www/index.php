<?php

session_start();

define ('IN_K', true);
define ('ROOT_PATH', dirname(__FILE__));
define ('CORE_PATH', ROOT_PATH.'/core');

$GLOBALS['config'] = array ();
require CORE_PATH.'/config.php';
require CORE_PATH.'/ext.php';
require CORE_PATH.'/siteconfig.php';
require CORE_PATH.'/includes/func.main.php';
require CORE_PATH.'/includes/func.upload.php';
require CORE_PATH.'/includes/class.kdb.php';

#if (@cfg('auth_type'))
#	require_once CORE_PATH.'/auth/'.cfg('auth_type').'.php';

require CORE_PATH.'/includes/init_rewrite.php';
#require CORE_PATH.'/includes/init_lang.php';

init_auth();

$GLOBALS['core'] = new core ();
$GLOBALS['core'] -> init ();
?>