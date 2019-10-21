function ValidMail() {
    var re = /^[\w-\.]+@[\w-]+\.[a-z]{2,4}$/i;
    var myMail = document.getElementById('email').value;
    var valid = re.test(myMail);
    if (valid) output = 'E-mail address writed correct!';
    else output = 'E-mail address writed incorrect!';
    document.getElementById('message').innerHTML = output;
    return valid;
}