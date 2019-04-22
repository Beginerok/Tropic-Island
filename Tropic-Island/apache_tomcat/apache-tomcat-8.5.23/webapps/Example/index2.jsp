<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Users</title>
</head>
<body>
<h2>Users List</h2>
<p><a href='<c:url value="/create" />'>Create new</a></p>
<table>
<tr><th>NickName</th><th>Password</th><th>email</th></tr>
<c:forEach var="user" items="${users}">
 <tr>
    <td>${user.nickname}</td> 
    <td>${user.password}</td>
    <td>${user.email}</td>
    <td>
    <a href='<c:url value="/edit?id=${user.id}" />'>Edit</a> |
    <form method="post" action='<c:url value="/delete" />' style="display:inline;">
        <input type="hidden" name="id" value="${user.id}">
        <input type="submit" value="Delete">
    </form>
 </td></tr>
</c:forEach>
</table>
</body>
</html>