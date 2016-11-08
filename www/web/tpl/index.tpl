<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<meta name="robots" content="index, follow" />
	<link rel="stylesheet" type="text/css" media="all" href="{{$_url}}/tpl/file-upload/fileuploader.css" />
	<link rel="stylesheet" type="text/css" media="all" href="{{$_url}}/tpl/css/style.css?v=4" />
	<title>{{$site_title}}</title>
</head>
<body>
	<script src="{{$_url}}/tpl/js/jquery-1.6.2.min.js" type="text/javascript"></script>
	
	{{login_form()}}
	<div id="main">
		{{if $page_title}}
			<div class="page_title">{{$page_title}}</div>
		{{/if}}
		<div class="main_area">{{$main}}</div>
	</div>
{{$debug}}

{{if $public_wdg}}
<script type="text/javascript">
reformal_wdg_domain    = "upetrows";
reformal_wdg_mode    = 0;
reformal_wdg_title   = "Upload service";
reformal_wdg_ltitle  = "Оставьте свой отзыв";
reformal_wdg_lfont   = "";
reformal_wdg_lsize   = "";
reformal_wdg_color   = "#FFA000";
reformal_wdg_bcolor  = "#516683";
reformal_wdg_tcolor  = "#FFFFFF";
reformal_wdg_align   = "left";
reformal_wdg_charset = "utf-8";
reformal_wdg_waction = 0;
reformal_wdg_vcolor  = "#9FCE54";
reformal_wdg_cmline  = "#E0E0E0";
reformal_wdg_glcolor  = "#105895";
reformal_wdg_tbcolor  = "#FFFFFF";
 
reformal_wdg_bimage = "7688f5685f7701e97daa5497d3d9c745.png";
 
</script>

<script type="text/javascript" language="JavaScript" src="http://reformal.ru/tab6.js?charset=utf-8"></script><noscript><a href="http://upetrows.reformal.ru">Upload service feedback </a> <a href="http://reformal.ru"><img src="http://reformal.ru/i/logo.gif" /></a></noscript>
{{/if}}
</body>
</html>