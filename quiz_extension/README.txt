------- Version -------------
This module is for Drupal 7.x.


------- Installation ----------
Install this module as normal Drupal module.


------- Dependencies ----------
Module has dependency on rules, services, and quiz module.
Please download these module if not installed already to
enable this module.


------- How to call rules and functions -----------

Rule component to add user tokens for specific term:
rules_invoke_component('quiz_extension_add_tokens', USER_ID, TERM_ID, NUMBER_OF_TOKENS);

Description: This rule add new entry if tokens don't exist for
user against term. Otherwise tokens will be updated to
passed tokens.



Rule component to consume user token on quiz creation:
rules_invoke_component('quiz_extension_consume_token', USER_ID, TERM_ID);

Description: This rule will consume one token form user account.
This code need to be called when integrating which front-end
to restrict the user not to create quiz if he/she has no 
token in his account.



Function to get user remaining tokens for specific term:
quiz_extension_get_user_tokens(USER_ID, TERM_ID);

Description: This function will return user's number of
remaining tokens for specific term. If you pass only USER_ID
it will return array having token details along-with term id.
