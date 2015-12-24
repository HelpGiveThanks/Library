//NOTE: THIS IS FOR NODE TAGS ONLY!  (I went crazy trying to figure out why a picture was not showing, and it turned out the table instance linked was for keywords not nodes.)

Case (
tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "jpg"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "gif"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "eps"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "jp2"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "psd"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "png"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "pct"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "pcs"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = ".qt"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "sgi"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "tga"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "tif"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "bmp"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "wmf"
or tagDefaultNodePrimary::pictureFileName1 ≠ "" and Right ( tagDefaultNodePrimary::pictureFileName1 ; 3 ) = "emf"

// The web viewer could show PDF image, but it is so small that it provides no useful information other than to put an icon in the viewer.  And since I am not putting icons for all the other types of media like movies, I the rule is no icons at all in this viewer.  The rule is this viewer is for pictures that help the user understand the tag and not the a file attached to the tag.  The next bit is the code neccessary to show a PDF:  or tagsCItationMenus::pictureFileName1 ≠ "" and rulePictureMediaLock::name = "text"
;
Let([

//In webviewer quotes operate differently from regular calc field.  The color hex numbers below have to be in quotes, so this would be the normal way to do that in calc field:
// If ( citationList::kmedia = "711201118061225" ; Quote ( "#eeeeee" ); Quote ( "#565e74" ) )
//But in the webviewer calc below is what works.
//Some PDF files have a transparent background which requires the white #eeeeee in order to show up.  It may be that this color background needs to be set at the category level for white bacground pdf, gifs, and pngs.

Bcolor = "#d7ceb4";

//purple "#473c5d"   tan = "#d7ceb4"

//Only fields from the layout's table will work when it comes to getting data to be used in web viewer.  So I had to create the field below instead of using the related field data which failed to show the picture.
Picture = tempSetup::DefaultPicturePrimary];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Picture & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"
)
;






defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "jpg"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "gif"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "eps"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "jp2"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "psd"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "png"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "pct"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "pcs"  
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = ".qt"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "sgi"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "tga"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "tif"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "bmp"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "wmf"
or defaultPictureRef::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "emf"
;

Let([

Fpath = defaultPictureRef::URL;

Bcolor = "#565e74"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"
) ;

defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "jpg"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "gif"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "eps"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "jp2"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "psd"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "png"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "pct"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "pcs"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = ".qt"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "sgi"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "tga"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "tif"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "bmp"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureTL::URL ; 3 ) = "wmf"
or defaultPictureTL::URL ≠ "" and Right ( defaultPictureRef::URL ; 3 )  = "emf"
;

Let([

Fpath = defaultPictureTL::URL;

Bcolor = "#565e74"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"
) ;



""   )
