Case (
tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "jpg"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "gif"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "eps"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "jp2"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "psd"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "png"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "pct"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "pcs"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = ".qt"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "sgi"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "tga"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "tif"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "bmp"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "wmf"
or tagDefaultTestSubject::pictureFileName1 ≠ "" and Right ( tagDefaultTestSubject::pictureFileName1 ; 3 ) = "emf"

// The web viewer could show PDF image, but it is so small that it provides no useful information
//other than to put an icon in the viewer.  And since I am not putting icons for all the other types
//of media like movies, I the rule is no icons at all in this viewer.  The rule is this viewer is for pictures
//that help the user understand the tag and not the a file attached to the tag.  The next bit is the
//code neccessary to show a PDF:  or tagsCItationMenus::pictureFileName1 ≠ ""
//and rulePictureMediaLock::name = "text"

 ; Let([

//In webviewer quotes operate differently from regular calc field.  The color hex numbers below
//have to be in quotes, so this would be the normal way to do that in calc field:
// If ( citationList::kmedia = "711201118061225" ; Quote ( "#eeeeee" ); Quote ( "#565e74" ) )
//But in the webviewer calc below is what works.
//Some PDF files have a transparent background which requires the white #eeeeee in order to
//show up.  It may be that this color background needs to be set at the category level for white
//bacground pdf, gifs, and pngs.

Bcolor =  "#d7ceb4";

//purple "#473c5d"   tan = "#d7ceb4"

//Only fields from the layout's table will work when it comes to getting data to be used in web
//viewer.  So I had to create the field below instead of using the related field data which failed
//to show the picture.

Picture = tempSetup::DefaultPictureTS];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\"
BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Picture & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"

 ) ;



defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "jpg"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "gif"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "eps"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "jp2"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "psd"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "png"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "pct"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "pcs"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = ".qt"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "sgi"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "tga"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "tif"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "bmp"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "wmf"
or defaultPictureRef_TS::URL ≠ "" and Right ( defaultPictureRef_TS::URL ; 3 ) = "emf"
;

Let([

Fpath = defaultPictureRef_TS::URL;

Bcolor = "#565e74"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\"
BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"

 ) ;

defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "jpg"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "gif"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "eps"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "jp2"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "psd"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "png"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "pct"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "pcs"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = ".qt"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "sgi"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "tga"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "tif"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "bmp"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "wmf"
or defaultPictureTL_TS::URL ≠ "" and Right ( defaultPictureTL_TS::URL ; 3 ) = "emf"
;

Let([

Fpath = defaultPictureTL_TS::URL;

Bcolor = "#565e74"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\"
BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"
 ) ;

""   )
