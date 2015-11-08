<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

if (!defined('IN_K')) exit ('No Access');

current_page ('profile');

function cnt_sort ($a, $b)
{
	return strnatcasecmp($a['data'], $b['data']);
}

class mod_user extends module_template
{
	function display ()
	{
		// Viewprofile
		if (input(1) && is_numeric(input(1)))
			return $this->show_user ();
			
		// Action
		if (!user('logged'))
		{
			// Try to login
			if (input(1,'login')) return $this->login();
		}

		if (user('logged') && input (1, 'logout'))
		{
			// Try to log-out
			return $this->logout();
		}

		# Final checks
		if (user('logged'))
		{
			#$GLOBALS['input'] = array ('user','profile','cnt');
			#return $this->profile ();
		} else
			return $this->login();

		// Else?
		@header ('Location: '.URL);
		exit ();
	}

	function login ()
	{
		site_title(lang('login_t'));
		page_title(lang('login_t'));
		
		$out = '';

		// Try to login?
		if (@$_POST['sub_login'])
		{
			$mail = @$_POST['mail'];
			$pass = @$_POST['pass'];
			
			$red = @$_POST['red'];
			if (!$red)
				$red = URL.'/';

			// has user?
			$data = kdb_select ('user', '*', '`mail`=\''.kdb_escape($mail).'\' AND `passwd`=\''.md5(md5(md5($pass))).'\' LIMIT 1');

			if (!$data)
			{
				// User is not found...
				// Drop cookie
				setcookie (cfg('auth_int_cookie_name'), '', time()-86400, '/', COOKIE_DOMAIN);

				// Error message
				//core_error_lng('login_e_p');

				$out .= '<div class="error_div"><p>'.lang('login_e_p').'</p></div><br/>';
				
			} else {
				$data = $data[0];

				// Status is OK?
				if ($data['status'] != 'ACTIVE')
				{
					if ($data['status'] == 'NOT_ACTIVATED')
					{
						// Not activated...
						$out .= '<div class="error_div">'.lang('login_e_a').'</div>';
					}
					if ($data['status'] == 'BANNED')
					{
						// Not activated...
						$out .= '<div class="error_div">'.lang('login_e_b').'</div>';
					}
				} else {
					// User exists...
					/*
					// Generate LoginKey
					$lk = sha1(md5($_SERVER['HTTP_USER_AGENT']).mt_rand().md5($mail).md5($pass).time());

					// Update DB
					db_update_by_id('site_users', $data['id'], array('login_key'=>md5($lk),'last_login'=>time(),'last_ip'=>$_SERVER['REMOTE_ADDR']));

					// All ok, set cookie and redirect;
					$c_data = base64_encode($data['id'].':'.base64_encode($lk));
					setcookie (cfg('auth_int_cookie_name'), $c_data, time()+intval(cfg('auth_int_session_time')), '/', COOKIE_DOMAIN);
					*/
					
					$this->create_session($data['id']);

					$msg = lang ('login_ok');
					$msg = str_replace ('{NAME}', $data['name'], $msg);
					redirect_msg ($red, $msg);
					exit ();
				}
			}
		}

		// Template
		/*$tpl = new tpl ('login_form');
		$tpl->v ('post',array_map('htmlspecialchars',$_POST));
		$out .= $tpl->get ();*/
		$fg = new cform ();
		$fg->add_title ('Авторизироваться в системе');
		$fg->add_input('text', lang('register_mail'), 'mail');
		$fg->add_input('password', lang('register_password'), 'pass');
		$fg->add_input('submit', '', 'sub_login', 'Войти');
		$fg->add_input('raw', '<tr><td align="center" colspan="2" class="formgen_input_area"><a href="'.URL.'/user/lost_password/">'.lang('t_lostp').'</a> / <a href="'.register_link().'">'.lang('t_register').'</a></td></tr>');
		$out .= $fg->get_form();
		
		return $out;
	}

	function logout ()
	{
		// Check key
		if (@$_GET['id']!=md5(md5(sha1(@$_COOKIE[cfg('auth_int_cookie_name')]))))
		{
			return core_error_lng('logout_e_k');
		}
		
		// Log out?
		kdb_update_by_id('user', user('id'), array('login_key'=>'-1','last_login'=>time(),'last_ip'=>$_SERVER['REMOTE_ADDR']));

		setcookie (cfg('auth_int_cookie_name'), '', time()-864000, '/', COOKIE_DOMAIN);

		$msg = lang ('login_out');
		$msg = str_replace ('{NAME}', user('name'), $msg);
		// echo $msg;
		redirect_msg (URL.'/', $msg);
		exit ();
	}

	function register ()
	{
		$out = '';
		return $out;
	}

	function create_session ($uid)
	{
		$data = kdb_select_one('user', '*', $uid);
		$lk = sha1(md5($_SERVER['HTTP_USER_AGENT']).mt_rand().md5($data['mail']).time().mt_rand(), true);
		$c_data = base64_encode($uid.':'.base64_encode($lk));
		setcookie (cfg('auth_int_cookie_name'), $c_data, time()+intval(cfg('auth_int_session_time')), '/', COOKIE_DOMAIN);
		kdb_update_by_id('user', $uid, array('login_key'=>md5($lk),'last_login'=>time(),'last_ip'=>$_SERVER['REMOTE_ADDR']));
	}

	function confirm ()
	{
		
		exit ();
	}

	function profile ()
	{
		
		exit();
	}

	function profile_menu ()
	{
	}

	function profile_index ()
	{
		return '<div style="text-align:center;padding:10px;">'.lang('profile_mt').'</div>';
	}
	
	function show_user ()
	{
		return '.i.';
	}

}
?>