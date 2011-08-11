<?php

/**
 * @file
 * community_tags.pages.inc
 *
 * Page handlers of Community Tags.
 *
 * @defgroup community_tags_pages Community Tags page handlers.
 * @{
 */

/**
 * Quick tag form.
 */
function community_tags_form($form, &$form_state, $edit, $title = NULL) {
  $vocabulary = taxonomy_vocabulary_load($edit['vid']);
 
 
  
  $access = user_access('tag content');

  $field = $edit['field'];

 
    $my_title = ('<br>Вы можете добавить новые Тэги</br>');
 


  $form['tags'] = array(
    '#type' => 'textfield',
    '#title' => $my_title,
    '#maxlength' => 100,
    '#default_value' => $edit['tags'],
    '#required' => FALSE,
    '#autocomplete_path' => 'taxonomy/autocomplete/' . $field['field_name'],
    '#attributes' => array('class' => array('form-tags form-tags-' . $edit['vid'])),
    '#access' => $access,
  );
  if ($edit['inline']) {
    $form['tags']['#size'] = 20;
  }

  if (!$access) {
    $destination = drupal_get_destination();
    $form['login'] = array(
      '#type' => 'markup',
      '#value' => '<div>' . t('<a href="@login">Login</a> or <a href="@register">register</a> to tag items', array('@login' => url('user/login', array('query' => $destination)), '@register' => url('user/register', array('query' => $destination)))) . '</div>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#access' => $access,
  );

  $form['node'] = array(
    '#type' => 'value',
    '#value' => $edit['node'],
  );

  $form['nid'] = array(
    '#type' => 'hidden',
    '#title' => t('NID'),
    '#value' => $edit['nid'],
  );

  $form['vid'] = array(
    '#type' => 'hidden',
    '#default_value' => $edit['vid'],
  );

  $nid = $edit['nid'];
  $vid = $edit['vid'];
  $names = $edit['names'];

  $form['#attached']['js'] = array(
    // Add a JavaScript setting. Note that when the key is a number, the 'data' property will be used.
    array(
      'data' => array('communityTags' => array('n_' . $nid => array('v_' . $vid => array('tags' => $names, 'url' => url('community-tags/js/' . $nid . '/' . $vid), 'add' => t('Add'), 'token' => drupal_get_token('community_tags_form'))))),
      'type' => 'setting'
    ),
  );

  return $form;
  // drupal_add_js(array('communityTags' => array('n_'. $node->nid => array('v_'. $vid => array('tags' => $names, 'url' => url('community-tags/js/'. $node->nid .'/'. $vid), 'add' => t('Add'), 'token' => drupal_get_token('community_tags_form'))))), 'setting');

}

/**
 * Submit callback for quick tag form.
 */
function community_tags_form_submit($form, &$form_state) {
  global $user;
  community_tags_taxonomy_node_save($form_state['values']['node'], array('tags' => array($form_state['values']['vid'] => $form_state['values']['tags'])), FALSE, $user->uid);

  $form_state['redirect'] = 'node/' . $form_state['values']['nid'];
}

/**
 * Theme the quick tag form.
 * @ingroup themeable
 */
function theme_community_tags_form($variables) {
  $form = $variables['form'];
  $output = '';

  // if(isset($form['cloud'])) {
  //   $output .= theme('form_element', array('#title' => $form['cloud']['#title']), drupal_render($form['cloud']));
  // }

  $output .= drupal_render_children($form);

  // We add the JS file this late, to ensure it comes after autocomplete.js.
  drupal_add_css(drupal_get_path('module', 'community_tags') . '/community_tags.css');
  drupal_add_js(drupal_get_path('module', 'community_tags') . '/community_tags.js');

  return $output;
}

/**
 * Menu callback:
 */
function community_tags_mypage($uid = NULL) {
  $uid = isset($uid) ? $uid : $GLOBALS['uid'];

  _community_tags_get_tag_result('user', 100, $uid);
}

