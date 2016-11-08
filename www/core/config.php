<?php
if (!defined('IN_K')) exit ('No Access');

$GLOBALS['config'] = array();

$GLOBALS['config']['ldb'] = array();
$GLOBALS['config']['ldb']['main'] = array(
	'type'    => 'mysqli',
	'host'    => 'localhost',
	'port'    => 3306,
	'user'    => 'www',
	'pass'    => 'www',
	'base'    => 'petro_upload',
	'charset' => 'UTF8',
);

$GLOBALS['config']['ext_control'] = false;

# Users control section
$GLOBALS['config']['auth_type'] = 'internal';
$GLOBALS['config']['auth_int_cookie_name'] = 'auth';
$GLOBALS['config']['auth_int_session_time'] = 10 * 86400;

$GLOBALS['config']['max_size'] = 4 * 1024 * 1024 * 1024;

$GLOBALS['config']['domain'] = 'hostname.com';
$GLOBALS['config']['default_lang'] = 'ru';
$GLOBALS['config']['site_tz'] = +3;
$GLOBALS['config']['mail'] = 'admin@hostname.com';
$GLOBALS['config']['mail_t'] = 'php';

$GLOBALS['config']['modules'] = array();

$GLOBALS['config']['debug'] = false;

?>
