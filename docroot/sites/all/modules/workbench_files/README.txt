/**
 * @file
 * README file for Workbench Files.
 */

Workbench 
A file management system that integrates with Workbench module.

CONTENTS
--------

1.  Introduction
1.1   Use-case
2.  Installation
3.  Permissions
4.  Configuration
5.  Using the module
6.  Troubleshooting
7.  Developer notes
8.  Feature roadmap


----
1.  Introduction

Workbench Files provides some basic file management within the Workbench
framework.

Essentially, Workbench Files allows users to see all files that have been
uploaded to the site.

----
1.1  Use-case

A typical request from clients is to re-use files that have already been
uploaded to a site.  Any type of file might be re-used: PDF, PNG, ZIP.

----
2.  Installation

Workbench is required in order to install Workbench Files.

Install the module and enable it according to Drupal standards.

----
3.  Permissions

There are no specific permissions to Workbench Files.

A user needs the "Access My Workbench" permission which is a general
Workbench permission setting.  If a user has Access My Workbench permission,
then she can access Workbench Files.

----
4.  Configuration

There is no specific configuration for Workbench Files.

----
5.  Using the module

When viewing My Workbench, you will see that Workbench Files adds a tab
called "File List".  Click this tab.

The File List tab provides a list of all files that have been uploaded to the
site.  Typical web image file formats (like jpg, png, gif) will include a
thumbnail of the image in the Type column.  Other file types like PDF display a
icon representing the file type.

The list includes which nodes use the file, the URL as well as the filepath
(e.g. public://filename.pdf).

----
6.  Troubleshooting

Current functionality for Workbench Files is quite minimal.  No tips to add at
this time.

----
7.  Developer notes

Workbench Files does not offer an API at this time.

---
8.  Feature roadmap

Workbench Files initial offering is quite small.  We expect big things to come
of this module.  In the long run, we want an Asset manager that fully
integrates with the entire content workflow process.  Some current plans:

 -- file management interface
  -- rename and move files
  -- provide meta data for  a file with a nice UI
  -- files like this widget when adding new files
 -- file field widget
  -- upload AND browse for File fields