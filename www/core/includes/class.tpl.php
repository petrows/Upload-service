<?php
if (!defined('IN_K')) exit ('No Access');

define ('TPL_C_DIR', ROOT_PATH.'/tmp/tpl_c');
define ('TPL_DIR', ROOT_PATH.'/tpl');

class tpl
{
	var $tpl_name;
	var $tpl_file;
	var $tpl_c_name;
	var $tpl_c_file;
	var $del_l = '{{';
	var $del_r = '}}';

	var $_tpl_var;
	
	function  tpl ($name = false)
	{
		if ($name)
			$this->tpl_name($name);
		
		// Basic vars
		$this->_tpl_var['lang'] = @$GLOBALS['lang'];
		$this->_tpl_var['user'] = @$GLOBALS['user'];
		$this->_tpl_var['siteconfig'] = @$GLOBALS['siteconfig'];
		$this->_tpl_var['_get'] = &$_GET;
		$this->_tpl_var['_post'] = &$_POST;
		$this->_tpl_var['_sess_name']	= session_name();
		$this->_tpl_var['_sess_id']		= session_id();
		$this->_tpl_var['_rnd']			= mt_rand();
		if (defined('URL'))
			$this->_tpl_var['_url'] = URL;
		if (defined('URL_FORUM'))
			$this->_tpl_var['_url_forum'] = URL_FORUM;
		if (defined('URL_ADMIN'))
			$this->_tpl_var['_url_admin'] = URL_ADMIN;
		if (defined('MODULE_URL'))
			$this->_tpl_var['_module_url'] = MODULE_URL;
		if (defined('MODULE_ADM'))
			$this->_tpl_var['_module_adm'] = MODULE_ADM;
	}

	function tpl_name ($name)
	{
		$name = trim(strtolower($name));
		$name = preg_replace ('/\.+/', '.', $name);
		
		$this->tpl_name = $name;
		$this->tpl_file = TPL_DIR.'/'.$this->tpl_name.'.tpl';

		$this->tpl_c_name = $this->tpl_name;
		$this->tpl_c_name = md5($this->tpl_c_name);
		$this->tpl_c_file = TPL_C_DIR.'/.ht.%%.'.$this->tpl_c_name.'.php';
	}

	function v ($name, $var)
	{
		$this->_tpl_var[strtolower($name)] = $var;
	}

	function compile_parse_vars_preg ($block)
	{
		$block = strtolower(@$block[1]);
		$block = explode('.', $block);
		$var_name = array_shift($block);
		$var_index = $block;
		if (count($var_index))
		{
			$var_index_t = array ();
			for ($x=0; $x<count($var_index); $x++)
			{
				$var_index_t[] = '[\''.$var_index[$x].'\']';
			}
			$var_index = implode('',$var_index_t);
		} else {
			$var_index = '';
		}

		return '@$this->_tpl_var[\''.$var_name.'\']'.$var_index;
	}

	function compile_parse_vars ($block)
	{
		// Compile vars PREG
		return preg_replace_callback('/\$([a-z0-9_.]+)/uims', array($this,'compile_parse_vars_preg'), $block);
	}

	function compile_block ($block)
	{
		$block = @$block[1];
		#$block = strtolower(@$block[1]);

		// IF construction?
		if (strtolower(substr($block, 0, 2)) == 'if')
		{
			// Yep!
			$block = '<?php if ('.$this->compile_parse_vars(trim(substr($block, 2))).') { ?>';
			return $block;
		}
		// End IF construction?
		if (strtolower(trim($block)) == '/if')
		{
			$block = '<?php } ?>';
			return $block;
		}
		if (strtolower(trim($block)) == 'else')
		{
			$block = '<?php } else { ?>';
			return $block;
		}

		// Default - show the var
		$block = '<?php echo '.$this->compile_parse_vars(trim($block)).'; ?>';
		return $block;
	}

	function compile ()
	{
		// Delete old TPL file...
		@unlink($this->tpl_c_file);

		$file_out = '<?php
/*
    Kblog simple compiled template.
    This script is generated, do not modify.
    Compiled: '.date('d.m.Y H:i:s').'
    TPL file: /'.$this->tpl_name.'.tpl
*/
?>';

		// Get original template...
		$tpl = file_get_contents($this->tpl_file);
		$tpl = preg_replace_callback('/'.preg_quote($this->del_l,'/').'(.*)'.preg_quote($this->del_r,'/').'(\r?\n)?/Uuims', array($this,'compile_block'), $tpl);
		$file_out .= $tpl;
		
		//echo $tpl;
		//return;
		$f = fopen ($this->tpl_c_file, 'w');
		if (!$f)
		{
			global_error('Enable to write compiled template!');
			exit ();
		}
		fputs ($f, $file_out);
		fclose ($f);
	}

	function get ($name = false)
	{
		if ($name)
			$this->tpl_name($name);
		
		// Tpl exists?
		if (!file_exists($this->tpl_file))
		{
			return '<p><b>Template error</b>: Enable to load template <code>'.$this->tpl_name.'</code>: file not found</p>';
		}

		// Has compiled tpl?
		if (!file_exists($this->tpl_c_file) || filemtime($this->tpl_c_file)<filemtime($this->tpl_file))
		{
			// No! Need to compile!
			$this->compile ();
		}

		// Return compiled TPL...

		// Set vars...
		// Run code
		$out = '';
		ob_start();
		include $this->tpl_c_file;
		//eval (file_get_contents($this->tpl_c_file));
		$out = ob_get_clean();
		return $out;
	}
}

?>