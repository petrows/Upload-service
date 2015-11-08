<?php

class captcha
{
	public $sid;
	public $id;

	public $cap_host = 'captcha.kmdtest.net';
	
	function init ($id)
	{
		$this->id = $id;
		$this->sid = md5(mt_rand()*time());
	}

	function get_file($url)
	{
		$url_d = parse_url($url);
		if (!@$url_d['host']) return false;
#print_r($url_d);
		$head = array ();
		$head[] = 'GET '.$url_d['path'].(@$url_d['query']?'?'.$url_d['query']:'').' HTTP/1.0';
		$head[] = 'Host: '.$url_d['host'];

		$head = implode("\r\n",$head);

		if (!$f=fsockopen($url_d['host'], 80)) return false;
		fwrite($f,$head."\r\n\r\n");
		
#echo $f; exit();
		$res = '';
		while ($s=trim(fgets($f)) && !feof($f)) {}

		while (!feof($f))
			$res .= fgets($f);
		return $res;
	}

	function get_form ()
	{
		$out = '';
		$out .= '
			<input type="hidden" name="captcha_sid" value="'.$this->sid.'"/>
			<noscript>
			<!-- form -->
			<input type="hidden" name="captcha_mode" value="iframe"/>
			<iframe width="200" height="150" frameborder="0" src="http://'.$this->cap_host.'/form.php?id='.$this->id.'&sid='.$this->sid.'&mode=iframe"></iframe>
			</noscript>
			<input type="hidden" name="captcha_mode" value="js"/>
			<script type="text/javascript" src="http://'.$this->cap_host.'/form.php?id='.$this->id.'&sid='.$this->sid.'&mode=js"></script>';
		return $out;

	}

	function check_form ()
	{
		$this->sid = @$_POST['captcha_sid'];
		$this->cap_data = @$_POST['cap_field'];
		if (!$this->sid) return false;
		$res = 0;
		if (@$_POST['captcha_mode'] == 'js')
		{
			$res = $this->get_file('http://'.$this->cap_host.'/api.php?a=check&sid='.$this->sid.'&id='.$this->id.'&js_data='.$this->cap_data);
		}
		if (@$_POST['captcha_mode'] == 'iframe')
		{
			$res = $this->get_file('http://'.$this->cap_host.'/api.php?a=check&sid='.$this->sid.'&id='.$this->id);
		}
		return $res == 1;
	}
}
?>