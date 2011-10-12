$Id: README.txt,v 1.5 2009/12/10 23:37:44 christianzwahlen Exp $

Drupal Text Size Module
-----------------------
Author - Christian Zwahlen info@zwahlendesign.ch
Requires - Drupal 7
License - GPL (see LICENSE.txt)

Description
-----------
This module display a adjustable text size changer or a zoom function on the page for a better web accessibility.

The zoom function is comparable to the text zoom function in Firefox 3, but this module resize also variable media objects, variable pixel images and vector images.

Advantages compared with browser zoom
-------------------------------------
1. Adjustable (increases/decreases step, minimum, maximum, standard and variable or three fixed values).
2. Resize region definable (for example a div with a ID "content": <div id="content">).
3. Browser independent.
4. One click function. No tutorial required.
5. Same handling in any browser (shortcuts).
6. Resize text, variable images and media objects (media objects or pixel images with "em" or "%" and SVG images).
7. Select menu availabe.
8. Display current text size (zoom size).

Features
--------
* WCAG and BITV conform.
* No Javascript and Cookies required. jQuery support.
* No CSS required.
* Minimum and maximum textsize.
* Text size values 0 - 999% available.
* Resize region definable with a ID or a class.
* Caching mode: "Normal" and "Aggressive" compatible.
* Uniform markin of menu, based on the open source browser Firefox 2.0 (www.mozilla.com/en-US/firefox/) (Increase Ctrl++, Decrease Ctrl+-, Normal Ctrl+0).
* Themable. See: textsize-html.tpl.php, textsize-image.tpl.php or textsize-form.tpl.php.
* By default, compatible to the Drupal standard Theme: "Garland".
* No "!important" in the CSS available (less code).
* No JavaScript support available.

Installation
------------
1. Move the textsize modul to the Drupal directory "sites/all/modules/".
2. Go to: "Configuration and modules", "Modules" (admin/config/modules/) and enable the module "Text Size".
3. Run the database update script "update.php" if required.

Settings
--------
1. Go to: "Configuration and modules", "People and permissions", "Permissions" ("admin/config/people/permissions#module-textsize) and set the different roles.
2. Go to: "Structure", "Blocks" ("admin/structure/block") and make the block "Text Size" visibile.
3. Go to: "Configuration and modules", "Content authoring", "Text Size configuration" ("admin/config/content/textsize") and change the settings if you want.
4. Go to: "Configuration and modules", "Regional and language", "Translate interface", "Import" ("admin/config/regional/translate/import") and import your language file (for German "/modules/pagestyle/translations/de.po") if it is necessary.

Theming
-------
Create Themes:
1.  Copy the files/directorys in your theme:
  1. textsize-text.tpl.php
  2. textsize-image.tpl.php
  3. textsize-form.tpl.php
  4. textsize.css
  5. images
2. Edit the PHP and CSS code in the files. Example: Image links, not in a list: Change the following elements: <ul>/</ul> to: <p>/</p>
  <li></li> to: <span class="display_hidden"> | </span>.
  WCAG/BITV 10.5: Adjacent hyperlinks have to be separated by printable characters surrounded by spaces. Warning: Not for: WCAG/BITV 13.6! Links are not in a list.
3. Edit the PHP templates (tpl.php) and textsize.css file. Example: "Image links, not in a list: Change the following elements: <ul>/</ul> to: <p>/</p>
  <li></li> to: <span class="display_hidden"> | </span>.
  WCAG/BITV 10.5: Adjacent hyperlinks have to be separated by printable characters surrounded by spaces. Warning: Not for: WCAG/BITV 13.6! Links are not in a list.
4. Edit the images. Create your own icons. The source file is in the directory: "/images/source/textsize.xcf". PNG images are for new browsers and GIF images for old browsers (Internet Explorer 6).

Download Themes: Edited templates are available from the developers website: http://www.zwahlendesign.ch/textsize.

Translations
------------
German
Importieren Sie die Datei "sites/all/modules/textsize/translations/de.po". unter "admin/build/translate/import" in die Deutsche Sprache, wenn es nötig ist.

Other languages
Open the file "sites/all/modules/textsize/translations/textsize.pot". in poEdit (http://www.poedit.net) or KBabel (http://kbabel.kde.org), translate the module in your language and save the file in "sites/all/modules/textsize/translations/" with a file suffix ".po".
