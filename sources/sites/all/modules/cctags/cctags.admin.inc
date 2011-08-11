<?php

/**
 * @file
 */

function cctags_settings() {
  $vocabularys =array();
  $items = _cctags_get_settings(NULL);
  $options =array();
  foreach (taxonomy_get_vocabularies() as $vocabulary) {
      $options[$vocabulary->vid] = $vocabulary->name;
  }
  $form['#tree']=TRUE;
  foreach ($items as $key => $item) {
  	$form['cctags_id'][] = array('#type' => 'hidden', '#value' => $key);
    $form['cctags_item'][$key]['cctags_item_name'] = array('#markup' => $item['name']);
    $form['cctags_item'][$key]['cctags_item_block'] = array('#type' => 'checkbox', '#default_value' => $item['block']);
    $form['cctags_item'][$key]['cctags_item_page'] = array('#type' => 'checkbox', '#default_value' => $item['page']);
    $form['cctags_item'][$key]['cctags_item_path'] = array('#markup' => (($item['page'])?l($item['page_path'], $item['page_path']):''));
    $form['cctags_item'][$key]['cctags_item_edit'] = array('#markup' => l(t('Settings'), 'admin/config/content/cctags/' . $item['cctid'] . '/edit'));
    $form['cctags_item'][$key]['cctags_item_del'] = array('#markup' =>  l(t('Delete'), 'admin/config/content/cctags/' . $item['cctid'] . '/delete'));
    $form['cctags_item'][$key]['cctags_item_id'] = array('#markup' => $item['cctid']);
    $form['cctags_item'][$key]['cctags_item_page_path'] = array('#type' => 'hidden', '#value' => $item['page_path']);
    $form['cctags_item'][$key]['cctags_item_page_title'] = array('#type' => 'hidden', '#value' => $item['page_title']);
    $form['cctags_item'][$key]['cctags_item_block_name'] = array('#type' => 'hidden', '#value' => $item['block_name']);
    $form['cctags_item'][$key]['cctid']= array('#type' => 'hidden', '#value' => $item['cctid'], '#tree' => TRUE);
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save cctags settings'),
  );

  return $form;
}

function cctags_settings_submit($form, &$form_state) {
  if (!form_get_errors()) {
    foreach ($form_state['values']['cctags_item'] as $key => $value) {
    	$block = $value['cctags_item_block'];
      $page =  $value['cctags_item_page'];
      $cctid = $value['cctid'];
      if ($block) {

        $block_name =check_plain(($form['cctags_item'][$key]['cctags_item_block_name']['#value'])?$form['cctags_item'][$key]['cctags_item_block_name']['#value']:$form['cctags_item'][$key]['cctags_item_name']['#markup']);
        db_update('cctags')
         ->fields(array('block_name' => $block_name))
         ->condition('cctid', $cctid)
         ->execute();
        }
      if ($page) {
        $page_path = $form['cctags_item'][$key]['cctags_item_page_path']['#value']?$form['cctags_item'][$key]['cctags_item_page_path']['#value']:'cctags/page/' . $cctid;

        db_update('cctags')
         -> fields(array('page_path' => $page_path))
         ->condition('cctid', $cctid)
         ->execute();
    }
       db_update('cctags')
         -> fields(array('block' => $block, 'page' => $page))
         ->condition('cctid', $cctid)
         ->execute();
    }

    drupal_set_message(t('The Cctags configuration has been updated.'));
     _cctags_clear_cache($cctid, 'all');
     menu_rebuild();
  }
}

function  cctags_settings_item($cctid) {
  drupal_add_js(drupal_get_path('module', 'cctags') .'/cctags-admin.js');
  $form = array();
  $maxlevel = 0;
  if ($cctid) {
    $items=_cctags_get_settings($cctid);
    $item = $items[$cctid];
    $form['cctags_cctid'] = array(
      '#type' => 'hidden',
      '#value' => $cctid,
     );
  }
  else {
    $item = array(
    'cctid' => NULL,
    'name' => '',
    'block' => false,
    'block_name' => '',
    'page' => false,
    'page_title' => '',
    'page_path' => '',
    'page_level' => 5,
    'page_amount' => 0,
    'page_sort' => 'title,asc',
    'page_mode' => 'mixed',
    'page_vocname' => '',
    'page_extra_class' => '',
    'item_data' => array(),
    );
  }
  $vocabularys =array();
  $v = taxonomy_get_vocabularies();
  foreach ($v as $vocabulary) {
  	$options[$vocabulary->vid] = $vocabulary->name;
    $tree[$vocabulary->vid] = taxonomy_get_tree($vocabulary->vid);
    $vocabularys[$vocabulary->vid]['name'] = $vocabulary->name;
    foreach ($tree[$vocabulary->vid] as $l) {
      if ($maxlevel<$l->depth) {
        $maxlevel = $l->depth;
      }
      $vocabularys[$vocabulary->vid][$l->depth] = $maxlevel;
    }
  }
  $form['cctags_name']= array(
    '#type' => 'textfield',
    '#title' => t('Cctags item name'),
    '#default_value' => $item['name'],
    '#required' => TRUE,
    );
  foreach ($vocabularys as $key => $value) {
  	$form['cctags_select_vocs'][$key] = array(
    '#type' => 'hidden',
    '#value' => $value['name'],
    );

  $form['cctags_select_' . $key] = array(
    '#type' => 'checkbox',
    '#title' => $value['name'],
    '#default_value' => (isset($item['item_data']['vocs']))?$item['item_data']['vocs'][$key]:FALSE,
    );
    foreach ($value as $k => $count_terms) {
      if (is_numeric($k)) {
        $form['cctags_select_' . $key . '_level_' . $k] = array(
          '#type' => 'checkbox',
          '#default_value' => (isset($item['item_data']['level'][$key][$k]))?$item['item_data']['level'][$key][$k]:FALSE,
        );
      }
    }
  }
  $form['cctags_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setting for block of this item cctags'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['cctags_block']['block'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable block for this cctags item'),
    '#default_value' => $item['block'],
  );
  $form['cctags_block']['block_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Block name'),
    '#maxlength' => 255,
    '#description' => t('A name of your block. Used on the block overview page. If empty then uses name this cctags  item.'),
    '#default_value' => $item['block_name'],
    '#prefix' => '<div class="cctags-settings-block">',
    '#suffix' =>'</div>',
  );
  $form['cctags_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setting for page of this item cctags'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['cctags_page']['page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable access page for this cctags item'),
    '#default_value' => $item['page'],
  );
  $form['cctags_page']['page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#maxlength' => 64,
    '#description' => t('A title of your page.'),
    '#default_value' => $item['page_title'],
    '#prefix' => '<div class="cctags-settings-page">',
  );

  $form['cctags_page']['page_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Page path'),
    '#maxlength' => 128,
    '#description' => t('Path to access of your page. If empty, predefined path cctags/page/%item-id.'),
    '#default_value' => $item['page_path'],
  );
  $c = _cctags_get_select_list('level');
  $form['cctags_page']['page_level'] = array(
    '#type' => 'select',
    '#options' => $c,
    '#title' => t('Number of levels fonts metrics'),
    '#default_value' => $item['page_level'],
    '#description' => t('The number of levels between the least popular tags and the most popular ones. Different levels will be assigned a different class to be themed in cctags.css'),
  );
  $op_sort = array('level,asc' => t('by level, ascending'), 'level,desc' => t('by level, descending'), 'title,asc' => t('by title, ascending'), 'title,desc' => t('by title, descending'), 'random,none' => t('random'));
  $form['cctags_page']['page_sort'] = array(
    '#type' => 'radios',
    '#title' => t('Tags sort order'),
    '#options' => $op_sort,
    '#default_value' => $item['page_sort'],
    '#description' => t('Determines the sort order of the tags on the page.'),
  );
  $amounts = _cctags_get_select_list('amount_tags');
  $form['cctags_page']['page_amount'] = array(
    '#type' => 'select',
    '#options' => $amounts,
    '#title' => t('Amount of tags on the per page'),
    '#default_value' => $item['page_amount'],
    '#description' => t('The amount of tags that will show up in a cloud on the per pages. if value equal 0, then all tags, for this cctags item, will be visible in one page.'),
  );
  $op_mode = array('group' => t('group by vocabulary'), 'mixed' => t('mixed vocabulary'));
  $form['cctags_page']['page_mode'] = array(
    '#type' => 'radios',
    '#title' => t('View page mode'),
    '#options' => $op_mode,
    '#default_value' => $item['page_mode'],
    '#description' => t('Determines the view mode of the tags on the page.'),
  );
  $form['cctags_page']['page_vocname'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cctags view page vocabulary name'),
    '#default_value' => $item['page_vocname'],
    '#description' => t('Determines the view vocabulary name(s).'),
  );

  $form['cctags_page']['page_extra_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Page wrapper extra class'),
    '#maxlength' => 64,
    '#description' => t('Extra class for page wrapper.'),
    '#default_value' => $item['page_extra_class'],
  );

  $form['cctags_select_block_maxlevel'] = array(
  '#type' => 'hidden',
  '#value' => $maxlevel,
  '#suffix' => '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save cctags item'),
  );
  return $form;
}

function  cctags_settings_add_item_validate($form, &$form_state) {
  cctags_settings_item_validate($form, &$form_state);
}
function  cctags_settings_edit_item_validate($form, &$form_state) {
  cctags_settings_item_validate($form, &$form_state);
}

function  cctags_settings_item_validate($form, &$form_state) {
  $error = TRUE;
  foreach ($form_state['values'] as $key => $value) {
    if (is_numeric($key)) {
      if ($form_state['values']['cctags_select_' . $key] == 1) {
        for ($i=0; $i<=$form_state['values']['cctags_select_block_maxlevel'];$i++) {
          if(isset($form_state['values']['cctags_select_' . $key . '_level_' . $i])) {
            if ($form_state['values']['cctags_select_' . $key . '_level_' . $i] == 1) {
              $error = FALSE;
              break;
            }
          }
        }
      }
    }
  }
  if ($error) {
    form_set_error('', t('Select at least one vocabulary and level.'));
  }
}

function cctags_settings_add_item_submit($form, &$form_state) {
  if (!form_get_errors()) {
      foreach ($form_state['values'] as $key => $value) {
        if (is_numeric($key)) {
          $item['vocs'][$key] = $form_state['values']['cctags_select_' . $key];
          for ($i=0; $i <= $form_state['values']['cctags_select_block_maxlevel']; $i++) {
            if(isset($form_state['values']['cctags_select_' . $key . '_level_' . $i])) {
            $item['level'][$key][$i] = $form_state['values']['cctags_select_' . $key . '_level_' . $i];
            }
          }
        }
      }
    $block_name = check_plain(($form_state['values']['block']==1)? ((empty($form_state['values']['block_name']))?$form_state['values']['cctags_name']:$form_state['values']['block_name']):'');
//    $page_path = ($form_state['values']['page']==1)? ((empty($form_state['values']['page_path']))?'cctags/page/' . $form_state['values']['cctags_cctid']:$form_state['values']['page_path']):'';
     $page_path = $form_state['values']['page_path'];
     $page_title = check_plain($form_state['values']['page_title']);
      $fields = array(
                'name' => check_plain($form_state['values']['cctags_name']),
                'block' => $form_state['values']['block'],
                'block_name' => $block_name,
                'page' => $form_state['values']['page'],
                'page_title' => $page_title,
                'page_path' => $page_path,
                'page_level' => $form_state['values']['page_level'],
                'page_amount' => $form_state['values']['page_amount'],
                'page_sort' => $form_state['values']['page_sort'],
                'page_mode' => $form_state['values']['page_mode'],
                'page_vocname' => $form_state['values']['page_vocname'],
                'page_extra_class' => $form_state['values']['page_extra_class'],
                'item_data' => serialize($item),
      );
      $cctid = db_insert('cctags')->fields($fields)->execute();
      if(empty($page_path) &&  $form_state['values']['page']){
      $page_path = 'cctags/page/' . $cctid;
      db_update('cctags')
      ->fields(
          array(
            'page_path' => $page_path,
          )
       )
       ->condition('cctid', $cctid)
       ->execute();
      }
      drupal_set_message(t('The Cctags item %name has been created.', array('%name' => check_plain($form_state['values']['cctags_name']))));

       _cctags_clear_cache($cctid, 'all');

      $form_state['redirect'] = 'admin/config/content/cctags';
  }
}

function cctags_settings_edit_item_submit($form, &$form_state) {
  if (!form_get_errors()) {
    foreach ($form_state['values'] as $key => $value) {
      if (is_numeric($key)) {
        $item['vocs'][$key] = $form_state['values']['cctags_select_' . $key];
        for ($i=0; $i<=$form_state['values']['cctags_select_block_maxlevel']; $i++) {
        	if (isset($form_state['values']['cctags_select_' . $key . '_level_' . $i])) {
          $item['level'][$key][$i] = $form_state['values']['cctags_select_' . $key . '_level_' . $i];
          }
        }
      }
    }
    $block_name = check_plain(($form_state['values']['block']==1)? ((empty($form_state['values']['block_name']))?$form_state['values']['cctags_name']:$form_state['values']['block_name']):'');
    $page_path = ($form_state['values']['page']==1)? ((empty($form_state['values']['page_path']))?'cctags/page/' . $form_state['values']['cctags_cctid']:$form_state['values']['page_path']):'';
    $cctid = $form_state['values']['cctags_cctid'];
      $num_updated = db_update('cctags')
      ->fields(array(
                'block' => $form_state['values']['block'],
                'block_name' => $block_name,
                'page' => $form_state['values']['page'],
                'page_title' => check_plain($form_state['values']['page_title']),
                'page_path' => $page_path,
                'page_level' => $form_state['values']['page_level'],
                'page_amount' => $form_state['values']['page_amount'],
                'page_sort' => $form_state['values']['page_sort'],
                'page_mode' => $form_state['values']['page_mode'],
                'page_vocname' => $form_state['values']['page_vocname'],
                'page_extra_class' => $form_state['values']['page_extra_class'],
                'item_data' => serialize($item),
        ))
       ->condition('cctid', $cctid)
       ->execute();
    drupal_set_message(t('The Cctags item %name has been updated.', array('%name' => check_plain($form_state['values']['cctags_name']))));
    _cctags_clear_cache($cctid, 'all');
    menu_rebuild();
    $form_state['redirect'] = 'admin/config/content/cctags';
  }
}

function  theme_cctags_settings($variables) {
 $form = $variables['form'];
 $output = '';
  $header = array(
  t('Cctags item name'),
  t('Cctag id'),
  t('Block'),
  t('Page'),
  t('Page path'),
  array('data' => t('Operation'), 'colspan' => '2'),
  );
  $rows = array();
  if(isset($form['cctags_id'])) {
  foreach ($form['cctags_id'] as $k => $value) {

  	if (is_numeric($k)) {
  		 $key = $value['#value'];
       if (is_numeric($key)) {
       	$row = array();
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_name']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_id']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_block']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_page']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_path']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_edit']));
        $row[] = array('data' => drupal_render($form['cctags_item'][$key]['cctags_item_del']));
        $rows[] = $row;
       }
     }
  }

 $form['cctags_item'] =  array(
      '#type' => 'markup',
      '#value' => theme('table', array('header' => $header, 'rows' => $rows)),
  );

 $form['cctags_item']= array_merge($form['cctags_item'],
    array(
    '#type' => 'fieldset',
    '#title' => t('Setting for cctags item'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#weight' => -20)
  );

  $output .= drupal_render($form['cctags_item']);
  $output .= drupal_render_children($form);//drupal_render($form);
  }
  return $output; //$output;
}

function  theme_cctags_settings_add_item($variables) {
	$form = $variables['form'];
  return theme('cctags_settings_item', array('form' => $form));
}

function  theme_cctags_settings_edit_item($variables) {
	$form = $variables['form'];
  return theme('cctags_settings_item', array('form' => $form));
}

function theme_cctags_settings_item($variables) {	$form = $variables['form'];
  $output = '';
  $header = array(t('Vocabulary name'));
  for ($i=0; $i<=$form['cctags_select_block_maxlevel']['#value']; $i++) {
    $header[] = t('Level') . ' ' . $i;
  }
  $rows = array();
  foreach ($form['cctags_select_vocs'] as $key => $value) {
  	if (is_numeric($key)) {
  		$row = array();
      $row[]= array('data' => drupal_render($form['cctags_select_' . $key]),'class' => array('cctags-voc'));

      for ($i=0; $i<=$form['cctags_select_block_maxlevel']['#value']; $i++) {
        $row[] = array('data' => drupal_render($form['cctags_select_' . $key . '_level_' . $i]),'class' => array('cctags-level'));
      }
      $rows[] = $row;
    }
  }
  $output .= drupal_render($form['cctags_name']);
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);

  return $output;
}

function  cctags_settings_add_item($form, $form_state) {
  return cctags_settings_item(NULL);
}

function  cctags_settings_edit_item($form, $form_state, $cctid) {
  return cctags_settings_item($cctid);
}

function  cctags_settings_delete_item($form, $form_state, $cctid) {
  $items =_cctags_get_settings($cctid);
  $item = $items[$cctid];
  $form['info'] = array('#type' => 'hidden', '#value' => $item['name']);
  $form['cctid'] = array('#type' => 'hidden', '#value' => $cctid);
  return confirm_form($form, t('Are you sure you want to delete the cctags item %name?', array('%name' => $item['name'])), 'admin/settings/content/cctags', '', t('Delete'), t('Cancel'));
}

function cctags_settings_delete_item_submit($form, &$form_state) {
	$cctid = $form_state['values']['cctid'];
  db_delete('cctags')
   ->condition('cctid', $cctid)
   ->execute();
  drupal_set_message(t('The cctags item %name has been removed.', array('%name' => $form_state['values']['info'])));
  _cctags_clear_cache($cctid, 'all');
  $form_state['redirect'] = 'admin/config/content/cctags';
}
