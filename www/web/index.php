<?php

session_start();

define('IN_K', true);
define('WEB_PATH', realpath(dirname(__FILE__)));
define('ROOT_PATH', realpath(dirname(__FILE__) . '/../'));
define('CORE_PATH', ROOT_PATH . '/core');
define('LTPL_C_DIR', ROOT_PATH . '/tmp/tpl_c');
define('LTPL_DIR', WEB_PATH . '/tpl');

$GLOBALS['config'] = array();
require CORE_PATH . '/config.php';
require CORE_PATH . '/ext.php';
require CORE_PATH . '/siteconfig.php';
require CORE_PATH . '/includes/func.main.php';
require CORE_PATH . '/includes/func.upload.php';
require CORE_PATH . '/includes/class.ldb.php';

require CORE_PATH . '/includes/init_rewrite.php';

init_auth();

$GLOBALS['core'] = new core ();
$GLOBALS['core']->init();
