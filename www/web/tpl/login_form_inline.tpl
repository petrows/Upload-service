<div class="login_area">
{{if $user.logged}}
	<div class="login_area_user">
		<table width="100%" cellpadding="10">
			<tr>
				<td align="left">{{user_link()}}</td>
				<td align="right">
					<a href="{{$_url}}/page/client/" style="font-weight:bold;font-size:120%;">Скачать клиент</a> / 
					<a href="{{$_url}}/upload/" style="font-weight:bold;font-size:120%;">{{$lang.fl_upload}}</a> / 
					<a href="{{$_url}}/files/" style="font-weight:bold;">{{$lang.fl_mylist}}</a> / 
					<a href="{{logout_link()}}">{{$lang.logout_t}}</a>
					</td>
			</tr>
		</table>
	</div>
{{else}}
	<div style="padding:5px;">
		<form method="post" action="{{$_url}}/user/login/">
			<input type="hidden" name="red" value="{{htmlspecialchars($current_url)}}"/>
			<input type="text" name="mail" class="login_inp" style="width:200px;" placeholder="{{$lang.t_login}}"/>
			<input type="password" name="pass" class="login_inp" style="width:200px;" placeholder="{{$lang.t_pass}}"/>
			<input type="submit" value="{{$lang.sub_login}}" name="sub_login"/>
		</form>
	</div>
{{/if}}
</div>