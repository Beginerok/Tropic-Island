function ValidMail() {
    var re = /^[\w-\.]+@[\w-]+\.[a-z]{2,4}$/i;
    var myMail = document.getElementById('email').value;
    var valid = re.test(myMail);
    if (valid) output = 'E-mail address writed correct!';
    else output = 'E-mail address writed incorrect!';
    document.getElementById('message').innerHTML = output;
    return valid;
}
function validate_form() {
                valid = true;
                if (document.form['nickname'] == "") {
                    alert("Вы не ввели своё имя");
                    valid = false;
                }
                if (document.form['password'] == "") {
                    alert("Вы не ввели свой password");
                    valid = false;
                }
                if (document.form['email'] == "") {
                    alert("Вы не ввели свой email");
                    valid = false;
                }
                return valid;
                
} 

