	
		<div style="padding:10px;">
			<div style="">
			<form method="post" action="{{$_url}}/user/login/">
				<table width="100%" cellpadding="3" cellspacing="0">
					<tr>
						<td class="form_t" width="100">{{$lang.t_login}}:</td>
						<td><input type="text" name="mail" style="width:200px;" value="{{$post.mail}}"/></td>
					</tr>
					<tr>
						<td class="form_t">{{$lang.t_pass}}:</td>
						<td><input type="password" name="pass" style="width:200px;" value=""/> &nbsp;&nbsp; <input type="submit" name="sub_login" value="{{$lang.sub_login}}" /></td>
					</tr>
				</table>
			</form>
			</div>
			</div>
			