Case (

tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "jpg"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "gif"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "eps"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "jp2"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "psd"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "png"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "pct"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "pcs"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = ".qt"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "sgi"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "tga"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "tif"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "bmp"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "wmf"
or tagMenus::pictureFileName2 ≠ "" and Right ( tagMenus::pictureFileName2 ; 3 )  = "emf"

// The web viewer could show PDF image, but it is so small that it provides no useful
//information other than to put an icon in the viewer.  And since I am not putting icons
//for all the other types of media like movies, I the rule is no icons at all in this viewer.
//The rule is this viewer is for pictures that help the user understand the tag and not
//the a file attached to the tag.  The next bit is the code neccessary to show a PDF:
//or tagsCItationMenus::pictureFileName1 ≠ "" and rulePictureMediaLock::name = "text"

;  Let([

//In webviewer quotes operate differently from regular calc field.  The color hex
//numbers below have to be in quotes, so this would be the normal way to do that in calc field:
// If ( citationList::kmedia = "711201118061225" ; Quote ( "#eeeeee" ); Quote ( "#565e74" ) )
//But in the webviewer calc below is what works.
//Some PDF files have a transparent background which requires the white #eeeeee in order to
//show up.  It may be that this color background needs to be set at the category level for
//white bacground pdf, gifs, and pngs.

Bcolor = "#d7ceb4" ;

//purple "#473c5d"   tan = "#d7ceb4"

//Only fields from the layout's table will work when it comes to getting data to be used in
//web viewer.  So I had to create the field below instead of using the related field data
//which failed to show the picture.

Picture = tagMenus::pictureFileName2];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Picture & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"

) ;


citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "jpg"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "gif"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "eps"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "jp2"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "psd"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "png"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "pct"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "pcs"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = ".qt"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "sgi"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "tga"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "tif"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "bmp"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "wmf"
or citationPicture2::URL ≠ "" and Right ( citationPicture2::URL ; 3 )  = "emf"
 ;

Let([

Fpath = citationPicture2::URL;

Bcolor = "#d7ceb4"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"

) ;




TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "jpg"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "gif"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "eps"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "jp2"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "psd"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "png"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "pct"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "pcs"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = ".qt"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "sgi"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "tga"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "tif"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "bmp"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "wmf"
or TLPicture2::URL ≠ "" and Right ( TLPicture2::URL ; 3 )  = "emf"
;

Let([

Fpath = TLPicture2::URL;

Bcolor = "#d7ceb4"];

"data:text/html,<html>¶

<body  bgcolor=\"" & Bcolor & "\" LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"  border=\"0\" style=\"border:0;scrolling:no\">¶¶" &

"<div align=\" center\"> <img src=\"" & Fpath & "\"  height=\"100% \"  border=\"0\"><br>¶"  &
"</body>¶
</html>¶"

) ;

""   )
