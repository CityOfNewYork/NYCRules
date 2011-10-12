<?php

/**
 * @file
 * Hooks provided by the Simplenews module.
 */

/**
 * @todo
 */
function hook_simplenews_issue_operations() {

}

/**
 * @todo
 */
function hook_simplenews_subscription_operations() {

}

/**
 * Collect recipients for a simplenews newsletter.
 *
 * Get both subscribed and unsubscribed recipients per newsletter category.
 * Special care should be taken to handle unsubscribed users correctly.
 *
 * @param $recipients
 *   Array of recipient objects with the following as minimum:
 *   $recipients['mail@example.com']
 *     recipient->mail      Email address
 *     recipient->status    Status flag (1, 0)
 *                          1 = may receive email, is subscribed;
 *                          0 = should not receive email, is unsubscribed.
 *     recipient->language  Language code of preferred email language
 * @param $scid
 *   Newsletter category ID.
 *
 * @todo Is 'uid' also required?
 *      recipient->uid       User ID of recipient (0 for anonymous)
 */
function hook_simplenews_recipients_alter(&$recipients, $tid) {
  $category = simplenews_category_load($tid);
  $recipients = simplenews_array_merge($recipients, simplenews_get_subscriptions_by_list($category->tid), 'simplenews_check_status');
}


/**
 * @todo
 */
function hook_simplenews_category_insert($category) {

}

/**
 * @todo
 */
function hook_simplenews_category_update($category) {

}

/**
 * @todo
 */
function hook_simplenews_category_delete($category) {

}

/**
 * @todo
 */
function hook_simplenews_mailing_list_insert($list) {

}

/**
 * @todo
 */
function hook_simplenews_subscriber_update($subscriber) {

}

/**
 * @todo
 */
function hook_simplenews_subscriber_insert($subscriber) {

}

/**
 * @todo
 */
function hook_simplenews_subscriber_delete($subscriber) {

}
