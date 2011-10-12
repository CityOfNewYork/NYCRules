<?php

/**
 * @file
 * Template file for theme('media_flickr_photoset');
 */
?>
<object width="<?php print $width; ?>" height="<?php print $height; ?>"> <param name="flashvars" value="offsite=true&lang=en-us&page_show_url=%2Fphotos%2F<?php print $user_id; ?>%2Fsets%2F<?php print $set_id; ?>%2Fshow%2F&page_show_back_url=%2Fphotos%2F<?php print $user_id; ?>%2Fsets%2F<?php print $set_id; ?>%2F&set_id=<?php print $set_id; ?>&jump_to="></param> <param name="movie" value="http://www.flickr.com/apps/slideshow/show.swf?v=104087"></param> <param name="allowFullScreen" value="true"></param><embed type="application/x-shockwave-flash" src="http://www.flickr.com/apps/slideshow/show.swf?v=104087" allowFullScreen="true" flashvars="offsite=true&lang=en-us&page_show_url=%2Fphotos%2F<?php print $user_id; ?>%2Fsets%2F<?php print $set_id; ?>%2Fshow%2F&page_show_back_url=%2Fphotos%2F<?php print $user_id; ?>%2Fsets%2F<?php print $set_id; ?>%2F&set_id=<?php print $set_id; ?>&jump_to=" width="<?php print $width; ?>" height="<?php print $height; ?>"></embed></object>
