<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

# Standart options
$GLOBALS['user'] = array();
$GLOBALS['user']['id'] = 0;
$GLOBALS['user']['name'] = 'Гость';
$GLOBALS['user']['login'] = 'guest';
$GLOBALS['user']['logged'] = false;
$GLOBALS['user']['tms'] = cfg('site_tz');
$GLOBALS['user']['lk'] = '-none-';

class auth
{
	function init()
	{
		$this->check_session();
	}
	
	function check_session()
	{
		if (!@$_COOKIE[ cfg('auth_int_cookie_name') ]) return false;
		$cd = explode(':', @base64_decode($_COOKIE[ cfg('auth_int_cookie_name') ]));
		if (!@$cd[0] || !@$cd[1]) return false;
		
		$uid = intval($cd[0]);
		$kid = base64_decode($cd[1]);
		
		# Check session...
		$data = ldb_select('user', '*', '`id`=\'' . $uid . '\' AND `login_key`=\'' . md5($kid) . '\' LIMIT 1');
		if (!$data) return false;
		
		# Login ok!
		$data = $data[0];
		
		# Check status
		if ($data['status'] != 'ACTIVE') {
			return false;
		}
		
		# Update DB
		ldb_update_by_id('user', $data['id'], array('last_login' => time(), 'last_ip' => ip2long($_SERVER['REMOTE_ADDR'])));
		# Update cookie
		setcookie(cfg('auth_int_cookie_name'), $_COOKIE[ cfg('auth_int_cookie_name') ], time() + intval(cfg('auth_int_session_time')), '/', COOKIE_DOMAIN);
		
		# Set global user data
		$GLOBALS['user'] = array();
		$GLOBALS['user']['id'] = $data['id'];
		$GLOBALS['user']['name'] = $data['name'];
		$GLOBALS['user']['login'] = $data['mail'];
		$GLOBALS['user']['logged'] = true;
		$GLOBALS['user']['is_admin'] = @$data['is_admin'];
		$GLOBALS['user']['adm_pages'] = @$data['adm_pages'] == 'Y';
		$GLOBALS['user']['adm_users'] = @$data['adm_users'] == 'Y';
		$GLOBALS['user']['adm_faq'] = @$data['adm_faq'] == 'Y';
		$GLOBALS['user']['tmz'] = @$data['tmz'];
		$GLOBALS['user']['lk'] = md5($_COOKIE[ cfg('auth_int_cookie_name') ]);
		$GLOBALS['user']['max_file'] = intval(@$data['max_file']);
		$GLOBALS['user']['max_total'] = intval(@$data['max_total']);
	}
}

function user($var)
{
	return @$GLOBALS['user'][ $var ];
}

function user_info($id = false)
{
	if (!$id) $id = user('id');
	$data = ldb_select_one('user', '*', $id);
	
	return $data;
}

function user_link($id = false, $blank = false)
{
	$data = user_info($id);
	if (!$data) return '<span class="user_link">Гость</span>';
	
	return '<span class="user_link"><img src="' . URL . '/tpl/img/icons/user.png" alt="" style="vertical-align:middle;"/> <a href="' . URL . '/user/' . $id . '/"' . ($blank ? ' target="_blank"' : '') . '>' . $data['name'] . '</a></span>';
}

function is_admin()
{
	if (user('logged') && user('is_admin') == 'Y') return true;
	
	return false;
}

function get_admins()
{
	$data = ldb_select('user', array('id'), '`is_admin`=\'Y\' ORDER BY `id`');
	
	return array_ids($data);
}

function user_password($login, $password, $is_md5 = false)
{
	if (!$is_md5)
		$password = md5($password);
	if ($u_data = ldb_select('user', array('id'), '`mail`=\'' . ldb_escape($login) . '\' AND `passwd`=\'' . md5(md5($password)) . '\' LIMIT 1')) {
		return $u_data[0]['id'];
	} else {
		return false;
	}
}

function login_form()
{
	if (user('logged')) {
		$tpl = new ltpl('login_form_inline');
		if (is_admin()) {
			
		}
		
		return $tpl->get();
	} else {
		$tpl = new ltpl('login_form_inline');
		
		# Current URL
		# dbg ($_SERVER);
		$red = $_SERVER['REQUEST_URI'];
		if (@$_POST['red'])
			$red = $_POST['red'];
		
		$tpl->v('current_url', $red);
		
		return $tpl->get();
	}
}

function login_link()
{
	return URL . '/user/login/';
}

function logout_link()
{
	return URL . '/user/logout/?id=' . md5(md5(sha1(@$_COOKIE[ cfg('auth_int_cookie_name') ])));
}

function register_link()
{
	return URL . '/user/register/';
}

function lostpwd_link()
{
	return URL . '/user/lost_password/';
}

function profile_link()
{
	return URL . '/user/profile/';
}

function login_req()
{
	return '<h3>Login required</h3>';
	
	@header('Location: ' . login_link());
	exit();
}

?>