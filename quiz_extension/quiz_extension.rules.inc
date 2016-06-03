<?php

/*
 * @file
 * Rules file - rules.inc
 */

/**
 * Implements hook_rules_action_info().
 */
function quiz_extension_rules_action_info() {
  return array(
    'quiz_extension_add_user_tokens' => array(
      'label' => t('Add user tokens'),
      'group' => t('Quiz'),
      'named parameter' => TRUE,
      'parameter' => array(
        'user' => array(
          'type' => 'integer',
          'label' => t('User ID'),
          'description' => t('User id.'),
        ),
        'term' => array(
          'type' => 'integer',
          'label' => t('Term ID'),
          'description' => t('ID of term.'),
        ),
        'tokens' => array(
          'type' => 'integer',
          'label' => t('Numebr of Tokens'),
          'description' => t('Number of tokens to create.'),
        ),
      ),
    ),
    'quiz_extension_consume_user_token' => array(
      'label' => t('Consume user token'),
      'group' => t('Quiz'),
      'named parameter' => TRUE,
      'parameter' => array(
        'user' => array(
          'type' => 'integer',
          'label' => t('User ID'),
          'description' => t('User id.'),
        ),
        'term' => array(
          'type' => 'integer',
          'label' => t('Term ID'),
          'description' => t('ID of term.'),
        ),
      ),
    ),
    'quiz_extension_get_user_tokens' => array(
      'label' => t('Display user tokens'),
      'group' => t('Quiz'),
      'named parameter' => TRUE,
      'parameter' => array(
        'user' => array(
          'type' => 'integer',
          'label' => t('User ID'),
          'description' => t('User id.'),
        ),
        'term' => array(
          'type' => 'integer',
          'label' => t('Term ID'),
          'description' => t('ID of term.'),
          'optional' => TRUE,
        ),
      ),
    ),
  );
}
