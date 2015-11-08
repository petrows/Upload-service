<?php

if (!defined('IN_K')) exit();

define ('IN_PHPBB', 1);

# Forum config
require $GLOBALS['config']['phpbb_path'].'/config.php';

if (!defined('PHPBB_INSTALLED') || !PHPBB_INSTALLED)
	exit ('Fatal error: forum is not found/installed/configured.');

# Global configs
$GLOBALS['config']['phpbb_table_prefix'] = $table_prefix;
$GLOBALS['config']['db_host']		= $dbhost;
$GLOBALS['config']['db_user']		= $dbuser;
$GLOBALS['config']['db_pass']		= $dbpasswd;
$GLOBALS['config']['db_base']		= $dbname;
$GLOBALS['config']['db_charset']	= 'UTF8';

# Include forum constants
require $GLOBALS['config']['phpbb_path'].'/includes/constants.php';
require $GLOBALS['config']['phpbb_path'].'/includes/functions.php';

define ('URL_FORUM', URL.'/'.basename(rtrim($GLOBALS['config']['phpbb_path'],'/')));

# Init user
$GLOBALS['user']['user']	= array ();
$GLOBALS['user']['logged']	= false;
$GLOBALS['user']['name']	= 'Гость';
$GLOBALS['user']['mail']	= 'gates@microsoft.com';
$GLOBALS['user']['tmz']		= $GLOBALS['config']['site_tz'];

class auth
{
	public $forum_config = array ();

	function init ()
	{
		# 1. Load the main board configs
		$this->load_forum_config();

		# 2. Init/check user session
		$this->check_session();
	}

	function load_forum_config ()
	{
		# Cache file exists?
		if (file_exists(ROOT_PATH.'/tmp/cache_phpbb_cfg.php') && filemtime(ROOT_PATH.'/tmp/cache_phpbb_cfg.php')>(time()-3600))
		{
			# Include the config
			require ROOT_PATH.'/tmp/cache_phpbb_cfg.php';
			if (count($this->forum_config)) return; # All ok
		}

		# Else - load from DB
		$this->forum_config = db_select (CONFIG_TABLE, array('config_name','config_value'), '`is_dynamic`=0');
		if (!$this->forum_config) return;

		# Save config to file
		$out = '<?php '."\n";
		$out .= '# Generated: '.datel('d.m.Y H:i:s')."\n";
		$out .= 'if (!defined(\'IN_K\')) exit (\'No data\');'."\n";

		$outa = array ();
		for ($x=0; $x<count($this->forum_config); $x++)
		{
			$outa[] = "\t".'\''.addslashes($this->forum_config[$x]['config_name']).'\'=>\''.addslashes($this->forum_config[$x]['config_value']).'\'';
		}
		$out .= '$this->forum_config = array ('."\n".implode(",\n",$outa)."\n".');'."\n";
		$out .= '?>';

		$f = fopen (ROOT_PATH.'/tmp/cache_phpbb_cfg.php', 'w');
		fputs ($f, $out);
		fclose ($f);
	}

	function check_session ()
	{
		# Init Default user
		$GLOBALS['user']	= array ();
		$GLOBALS['user']['id']		= ANONYMOUS;
		$GLOBALS['user']['logged']	= false;
		$GLOBALS['user']['name']	= 'Guest';
		$GLOBALS['user']['mail']	= 'gates@microsoft.com';
		$GLOBALS['user']['tmz']		= $GLOBALS['config']['site_tz'];
		$GLOBALS['user']['ip']		= preg_replace('/[^0-9A-F:.]/', '', strtolower(@$_SERVER['REMOTE_ADDR']));
		$GLOBALS['user']['is_admin']= false;

		# has session data?
		if (!@$_COOKIE[phpbb_cfg('cookie_name').'_sid'])
			return false; # No cookie

		$sid = preg_replace('/[^a-z0-9]/', '', strtolower($_COOKIE[phpbb_cfg('cookie_name').'_sid']));
		$browser = (!empty($_SERVER['HTTP_USER_AGENT'])) ? htmlspecialchars((string) $_SERVER['HTTP_USER_AGENT']) : '';;

		$data = db_query('SELECT u.*, s.* FROM '.SESSIONS_TABLE.' s, '.USERS_TABLE.' u WHERE s.session_id = \''.$sid.'\' AND u.user_id = s.session_user_id');
		if (!$data)
		{
			# Is a session revival?
			
			# No session data
			$this->delete_session_cookie();
			return false;
		}
		$data = $data[0];

		# Check ip
		if (strpos($GLOBALS['user']['ip'], ':') !== false && strpos($GLOBALS['user']['ip'], ':') !== false)
		{
			$s_ip = short_ipv6($data['session_ip'], phpbb_cfg('ip_check'));
			$u_ip = short_ipv6($GLOBALS['user']['ip'], phpbb_cfg('ip_check'));
		} else {
			$s_ip = implode('.', array_slice(explode('.', $data['session_ip']), 0, phpbb_cfg('ip_check')));
			$u_ip = implode('.', array_slice(explode('.', $GLOBALS['user']['ip']), 0, phpbb_cfg('ip_check')));
		}

		$s_browser = (phpbb_cfg('browser_check')) ? trim(strtolower(substr($data['session_browser'], 0, 149))) : '';
		$u_browser = (phpbb_cfg('browser_check')) ? trim(strtolower(substr($browser, 0, 149))) : '';

		# Final session check!
		if ($s_ip === $u_ip && $s_browser === $u_browser)
		{
			# All ok!
		} else {
			# Fail!
			return false;
		}

		$GLOBALS['user']['logged']	= ($data['user_id'] != ANONYMOUS && ($data['user_type'] == USER_NORMAL || $data['user_type'] == USER_FOUNDER)) ? true : false;
		$GLOBALS['user']['id']		= intval($data['user_id']);
		$GLOBALS['user']['name']	= $data['username'];
		$GLOBALS['user']['mail']	= $data['user_email'];
		$GLOBALS['user']['tmz']		= floatval($data['user_timezone']);
		$GLOBALS['user']['sid']		= $sid;
		$GLOBALS['user']['color']	= $data['user_colour'];
		$GLOBALS['user']['is_admin']= ($data['user_type'] == USER_FOUNDER);

		$GLOBALS['user']['avatar']		= $data['user_avatar'];
		$GLOBALS['user']['avatar_type']	= $data['user_avatar_type'];
		$GLOBALS['user']['avatar_x']	= $data['user_avatar_width'];
		$GLOBALS['user']['avatar_y']	= $data['user_avatar_height'];

		# Update user cookies
		setcookie(phpbb_cfg('cookie_name').'_sid', $sid, time()+3600, phpbb_cfg('cookie_path'), phpbb_cfg('cookie_domain'));

		# Update session time - only one per 1 min
		if (time() - $data['session_time'] > 60)
			db_update_by_id(SESSIONS_TABLE, $sid, array('session_time'=>time()), 'session_id');

		return true; # All is ok, user is here
	}

	function delete_session_cookie ()
	{

	}
}

function phpbb_cfg ($var)
{
	if (!@$GLOBALS['auth']) return false;
	return @ $GLOBALS['auth']-> forum_config[$var];
}

function user ($var)
{
	return @$GLOBALS['user'][$var];
}

function user_info ($id = false)
{
	if ($id === false)
	{
		# Self
		if (!user('logged')) return array ();
		return $GLOBALS['user'];
	} else {
		$data = db_select_one(USERS_TABLE, '*', $id, 'user_id');
		if (!$data) return array ();
		if ($data['user_type'] != USER_NORMAL && $data['user_type'] != USER_FOUNDER) return array ();

		$out = array ();
		$out['id'] = $id;
		$out['name']	= $data['username'];
		$out['mail']	= $data['user_email'];
		$out['tmz']		= floatval($data['user_timezone']);
		$out['sid']		= '0';
		$out['color']	= $data['user_colour'];

		$out['avatar']		= $data['user_avatar'];
		$out['avatar_type']	= $data['user_avatar_type'];
		$out['avatar_x']	= $data['user_avatar_width'];
		$out['avatar_y']	= $data['user_avatar_height'];

		return $out;
	}
}

function user_link ($id = false, $is_blank = false)
{
	$uinfo = user_info ($id);
	if (!$uinfo) return 'Гость';
	return '<a href="'.URL_FORUM.'/memberlist.php?mode=viewprofile&u='.$uinfo['id'].'" class="user_link" style="color:#'.$uinfo['color'].';"'.($is_blank?' target="_blank"':'').'>'.$uinfo['name'].'</a>';
}

function is_admin ()
{
	if (user('logged') && user('is_admin') == 'Y') return true;
	return false;
}

function get_admins ()
{
	$data = db_select ('site_users', array('id'), '`is_admin`=\'Y\' ORDER BY `id`');
	return array_ids($data);
}

function user_password ($login, $password)
{
	$data = db_select_one(USERS_TABLE, '*', $login, 'username');
	if (!$data) return false;
	if ($data['user_id'] != user('id')) return false;

	return phpbb_check_hash($password, $data['user_password']);
}

function login_form ()
{
	if (user('logged'))
	{
		$tpl = new tpl('login_form_inline');
		return $tpl->get();		
	} else {
		$tpl = new tpl('login_form_inline');
		$tpl->v('current_url',  htmlspecialchars($_SERVER['REQUEST_URI']));
		return $tpl->get();		
	}
}

function login_link ()
{
	return URL_FORUM.'/ucp.php?mode=login';
}

function logout_link ()
{
	return URL_FORUM.'/ucp.php?mode=logout&sid='.user('sid');
}

function register_link ()
{
	return URL_FORUM.'/ucp.php?mode=register';
}

function lostpwd_link ()
{
	return URL_FORUM.'/ucp.php?mode=sendpassword';
}

function profile_link ()
{
	return URL_FORUM.'/ucp.php';
}

?>