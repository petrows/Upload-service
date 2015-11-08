<?php
if (!defined('IN_K')) exit ('No Access');

class core
{
	public $error = array ();
	public $warning = array ();

	public $global_msg = false;

	public $mainhref = '';
	public $block_left = '';

	public $module_name = '';

	public $page_title = array();
	public $site_title = '';
	public $top_text = '';
	
	public $current_page = '';

	public $meta_kw	= '';
	public $meta_desc	= '';
	
	public $public_wdg = true;

	function init ()
	{
		require_once CORE_PATH.'/includes/init_lang.php';
		$this->top_text = '<img src="'.URL.'/tpl/images/design/index-img.png" alt=""/>';

		$this->load_module ();
		$this->display ();
	}

	function load_module ()
	{
		// If we have errors & global msg - skip module loading
		if ($this->global_msg || $this->error)
			return;

		// Have module?
		if (!input(0))
		{
			$GLOBALS['input'][0]='index';
		}


		if (input(0,'banner_top'))
			return $this->load_banner_top();
		
		# First - we want static page?		
		/*if (input(0))
		{
			if ($page=kdb_select_one('page', array('id','name'), input(0),'name'))
			{
				$GLOBALS['input'][0]='page';
				$GLOBALS['input'][1]=$page['name'];
			}
		}*/

		$module_name = preg_replace ('/[^a-z0-9_-]/', '', strtolower(input(0)));
		$this->module_name = $module_name;
		
		// Search file
		if (!file_exists(CORE_PATH.'/modules/mod_'.$module_name.'.php'))
		{
			// No file
			page_title('404 - Страница не найдена');
			return core_error_404 ();
		}

		# Calculate current page...
		#$std_pages = array ('news','')

		require_once CORE_PATH.'/modules/mod_'.$module_name.'.php';
		
		// Load class
		$module_class = 'mod_'.$module_name;
		/*if (!method_exists($module_class, 'display'))
		{
			// No file
			return core_error_404 ();
		}*/

		$obj = new $module_class ();
		$this->mainhref = $obj->display ();
	}

	function menu_left ()
	{
	}

	function menu_right ()
	{
	}




	function display ()
	{

		$index_tpl = 'index';

		$tpl = new tpl ($index_tpl);
		
		// fatal errors?
		if ($this->global_msg)
		{
			// Show global message (login error?)
			$this->mainhref = $this->global_msg;
		}

		// Errors & warnings
		if ($this->error)
		{
			// Add fatal errors
			$out = '';
			$out .= '<div class="error_div">';
			$out .= '<h3>'.lang('e_title').'</h3>';

			if (count($this->error)>1)
			{
				$out .= '<ul>';
				foreach ($this->error as $k=>$e)
				{
					$out .= '<li>'.$e.'</li>';
				}
				$out .= '</ul>';
			} else {
				$out .= '<p>'.$this->error[0].'</p>';
			}
			
			$out .= '</div>';

			$this->mainhref = $out.$this->mainhref;
		}

		$tpl->v ('main', $this->mainhref);

		// Site title
		if (!$this->site_title)
		{
			$this->site_title = $GLOBALS['siteconfig']['site_title'];
		} else {
			$this->site_title = $GLOBALS['siteconfig']['site_title'].' : '.$this->site_title;
		}
		if ($this->page_title)
		{
			$this->page_title[count($this->page_title)-1] = '<b>'.$this->page_title[count($this->page_title)-1].'</b>';
			$this->page_title = implode(' / ',$this->page_title);
		}

		if (!$this->meta_kw && !$this->meta_desc)
		{
			//$metad = db_select_one ('site_pages', array('meta_kw','meta_desc'),'index','name');
			$this->meta_kw		= @$metad['meta_kw'];
			$this->meta_desc	= @$metad['meta_desc'];
		}

		
		$tpl->v ('main',		$this->mainhref);
		$tpl->v ('meta_kw',		$this->meta_kw);
		$tpl->v ('meta_desc',	$this->meta_desc);
		$tpl->v ('site_title',	$this->site_title);
		$tpl->v ('page_title',	$this->page_title);
		
		$tpl->v ('public_wdg',  $this->public_wdg);


		$tpl->v ('cookie_domain', COOKIE_DOMAIN);
		$tpl->v ('code_bottom', @$GLOBALS['siteconfig']['code_bottom']);

		if (@cfg('debug'))
			$tpl->v ('debug', kdb_log_html());
		
		echo $tpl->get ();
	}
}
?>