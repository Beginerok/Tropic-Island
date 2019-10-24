<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Sign Up</title>
<link rel="stylesheet" href="create.css">
<script type="text/javascript" src="create.js"></script>
</head>
<body>
<div id="CenterBlock">
<form method="post"  onsubmit="return ValidMail();">
<h3>Create Account</h3>
<!--
<label class="labeler">Username</label><br>
-->
<input class="inputer" name="nickname" placeholder="Username *" required/><br><br>
<!--
<label class="labeler">Password</label><br>
-->
<input class="inputer" name="password" type="password" placeholder="Password *" required/><br><br>
<!--
<label class="labeler">Email</label><br>
-->
<input class="inputer" id="email" name="email" value="" placeholder="E-mail *" required/><br><br>
<input class="button" type="submit" value="Sign Up"/>
<p id="message" >Enter your information</p>
</form>
</div>
</body>
</html>
