<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

define ('ROOT_PATH', realpath(dirname(__FILE__).'/../../'));
define ('CORE_PATH', ROOT_PATH.'/core');

define ('IN_K', true);

require CORE_PATH.'/siteconfig.php';

define ('URL', $GLOBALS['siteconfig']['site_url']);

set_time_limit(0);

require CORE_PATH.'/config.php';

require CORE_PATH.'/includes/func.main.php';
require CORE_PATH.'/includes/func.upload.php';

function kill_pid ($pid)
{
	$pid = intval($pid);
	if (!$pid) return;
	if ($pid == getmypid()) return;
	system('kill '.$pid);
}

# DB
require CORE_PATH.'/includes/class.kdb.php';
require CORE_PATH.'/auth/internal.php';

# Lang
require CORE_PATH.'/lang/ru.php';

?>