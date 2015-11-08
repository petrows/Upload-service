{{if !$_post}}
<script type="text/javascript">
	var d = new Date ();
	d = -d.getTimezoneOffset()/60;
	{{if $tmz_summer}}d = d-1;{{/if}}
	document.getElementById('tmz').selectedIndex = 12+(d);
</script>
{{/if}}