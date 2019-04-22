<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Edit Users</title>
</head>
<body>
<h3>Edit Users</h3>
<form method="post">
<input type="hidden" value="${users.id}" name="id" />
<label>NickName</label><br>
<input name="nickname" value="${users.nickname}" /><br><br>
<label>Password</label><br>
<input name="password" value="${users.password}" /><br><br>
<label>Email</label><br>
<input name="email" value="${users.email}" /><br><br>
<input type="submit" value="Send" />
</form>
</body>
</html>