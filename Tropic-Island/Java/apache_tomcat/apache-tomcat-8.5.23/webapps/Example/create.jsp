<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Create User</title>
<link rel="stylesheet" href="create.css">
<script type="text/javascript" src="create.js"></script>
</head>
<body>
<h1>Create Account</h1>
<p id="message" >Enter your information</p>
<div id="CenterBlock">
<form method="post"  onsubmit="return ValidMail()">
<label class="labeler">NickName</label><br>
<input class="inputer" name="nickname"/><br><br>
<label class="labeler">Password</label><br>
<input class="inputer" name="password" type="password" /><br><br>
<label class="labeler">Email</label><br>
<input class="inputer" id="email" name="email" /><br><br>
<input class="button" type="submit" value="Save"/>
</form>
</div>
</body>
</html>
