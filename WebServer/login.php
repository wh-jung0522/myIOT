<?php
    $user = check_param("user");
    $pass = check_param("pass");
    
    session_start();
            
    if (checkUser($user, $pass)) {
            $_SESSION["login"] = $user;
            $_SESSION["begin"] = date("F j, Y, g:i:s a");
            header("Location: image_paging_test.php?user=$user");
    } else {
            header("Location: index.php");
    }
    
    function check_param($var) {
        if (!isset($_POST[$var]) || $_POST[$var] == "") {
            die("Error : missing required parameter '$var'");
        }
        return trim($_POST[$var]);
    }
    
    function checkUser($user, $pass) {
        $hash_pass = hash("sha256", $pass);
        $usersfile = "users.dat";
        $granted = false;
        $users = explode("\n",file_get_contents($usersfile));
        foreach ($users as $each) {
            $info = explode(":",$each);
            if ( $user == trim($info[0]) && $hash_pass == trim($info[1]) ) {
                $granted = true;
                break;
            }
        }
    return $granted;
    }

?>