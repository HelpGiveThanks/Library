//IMPORTANT: References to related tables are only allowed in Case and If functions in a web viewer, but NOT to display media.  ONLY fields from a layout's table will display media in a web viewer.  Just wanted to make a note of this because it took a lot of tinkering to figure out.

//IMPORTANT: Spaces and quote types are parsed as code in some parts the web viewer!  For example, "<img works, but "< img fails.  Straight quotes " work, but curled quotes “ fail.  NOTE: The base64 code has been tested and works for all listed filetypes below.  Any change in spacing or coding will probably fail some file types, but not others.

//IMPORTANT: Base64 file size should be kept under 4 MB on slower computers and for best results under 1 MB.  Allowing larger files will just lock up FileMaker while Base64 tries to build the file and show it.  Solution to lock up = crash FileMaker, restart, and reduce file size for displaying container media on the set defaults layout.

//REFERENCES: Found the following web-viewer related references valuable:   1) On showing a container field's content in the web-viewer http://www.filemakergeek.com/blog/2014/5/21/container-field-images-in-the-web-viewer    2) Using 'object' instead of 'img', 'video', etc to identify src type https://www.w3.org/TR/html401/struct/objects.html    3) A nifty open-source pluggin for the web viewer http://www.goya.com.au/baseelements/plugin 4) Base64 mime types for encoding various file formats https://github.com/rapid7/mime-types/tree/master/lib/mime/types 5)  PDF Thumbnails in FileMaker explained/tutorial https://filemakerhacks.com/2015/05/28/pdf-thumbnails-in-filemaker-14/

//Each section of the code below begins with a test.  If passed, then variables are calculated, and something is displayed.  

//-----START
//———————————————Test
//———————————————Variables
//———————————————Display
//-----END

//If a test fails, then the computer goes to the next test, and so on.

//THIS WEB-VIEWER CAN ...
//Show FileMaker container-field contents
//-----START: Show Thumbnail of Image in Container Field
//-----START: Show Container Field File Info
//-----START: Show Container Field PDF or Video Media

//Show web media
//-----START: Show YouTube Web Media
//-----START: Show Other Web Media Info
//-----START: Show Other Web Media

//Show hard disk drive (HDD) media
//-----START: Show HDD Media Info
//-----START:  Show HDD Media

//CASE BEGIN (figure out what this record has for the web-viewer to show and show it)
Case (



//-----START: Show Thumbnail of Image in Container Field


//------------------------------Test
( (
//-----Picture
Right ( refPicture2::picture ; 3 ) = "bmp" or
//EPS doesn’t work!!! Right ( citationPicture2::picture ; 3 ) = "eps" or
Right ( refPicture2::picture ; 3 ) = "gif" or
Right ( refPicture2::picture ; 4 ) = "jpeg" or
Right ( refPicture2::picture ; 3 ) = "jpg" or
Right ( refPicture2::picture ; 3 ) = "png" or
Right ( refPicture2::picture ; 3 ) = "psd" or
Right ( refPicture2::picture ; 3 ) = "sgi" or
Right ( refPicture2::picture ; 3 ) = "tga" or
Right ( refPicture2::picture ; 3 ) = "tif" or
Right ( refPicture2::picture ; 4 ) = "tiff"
) = 1  and  refPicture2::picture ≠ "") and Right ( Get ( FilePath ) ; 3 ) ≠ "fp7" ;


//------------------------------Variables
Let([
BACKGROUND_COLOR = "#565e74" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

"<img src='data:image/jpg;base64," &
B64EncodeFromFM7 ( refPicture2::pictureThumbnail ) & "'/  height=\"100%\"  >" &

"</div></body></html>" ) ;

//-----END






//-----START: Show Container Field File Info (because file type cannot be displayed by FileMaker, or file is too large, or both)


//------------------------------Test
( (
//-----Picture
//EPS images can contain characters that base64 can’t read, so display file name instead of file.
//Right ( citationPicture2::picture ; 3 ) = "eps" or
//-----PDF
Right ( refPicture2::picture ; 3 ) = "pdf" or
//-----Video
Right ( refPicture2::picture ; 3 ) = "mov" or
Right ( refPicture2::picture ; 3 ) = "mp4" or
Right ( refPicture2::picture ; 3 ) = "m4v"
) = 0  and  refPicture2::picture ≠ "") or
refPicture2::picture ≠ "" and Round ( Length ( refPicture2::picture ) / 1000000; 2 ) > refPicture2::PictureFileSizeCalc or
refPicture2::picture ≠ "" and Right ( Get ( FilePath ) ; 3 ) = "fp7" ;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Let ( x = Length ( GetValue (  refPicture2::picture  ; 1 ) ) ;
Substitute ( Substitute ( Case (
Middle ( refPicture2::picture ; x - 3 ; 1 ) = "." ;
     Left ( refPicture2::picture ; x - 4 ) ;
     Left ( refPicture2::picture ; x - 5 ) ) ; " " ; "_" )  ; "-" ; "_" ) ) ;

FILEMAKER_OLDVERSION = Case ( Right ( Get ( FilePath ) ; 3 ) = "fp7" ; "(fp7 can't show container thumbs) " ) ;

FILE_TYPE = Let ( x = Position ( refPicture2::picture ; "." ; 1 ; Length ( Filter ( refPicture2::picture ; "." ) ) ) + 1 ;
   Middle ( refPicture2::picture ; x ; 20 ) ) ;

FILE_SIZE = Let ( x = Length ( refPicture2::picture ) ;
Case (
     Round ( x / 1000000; 2 ) < 1 ;
     Middle ( x ; 1 ;3 )  & " KB";
     Round ( x / 1000000; 1 )  & " MB" ) ) ;

MODULE =   "(reference)" ;

BACKGROUND_COLOR = "#fff" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

FILE_NAME &
"<br>" &
FILEMAKER_OLDVERSION &
FILE_TYPE &
"<br>" &
FILE_SIZE &
"<br>" &
MODULE &

"</div></body></html>" ) ;

//-----END






//-----START: Show Container Field PDF or Video Media


//------------------------------Test
refPicture2::picture ≠ "" ;


//------------------------------Variables
Let([
FILE_TYPE = Case (
//-----PDF
Right ( refPicture2::picture ; 3 ) = "pdf"; "object data='data:application/pdf" ;
//-----Video
Right ( refPicture2::picture ; 3 ) = "mov"; "video src='data:video/quicktime" ;
Right ( refPicture2::picture ; 3 ) = "mp4"; "video src='data:video/mp4" ;
Right ( refPicture2::picture ; 3 ) = "m4v"; "video src='data:video/mp4" ;
"unknown" ) ;

HEIGHT_WIDTH = Case ( Right ( refPicture2::picture ; 3 ) = "mp4" or Right ( refPicture2::picture ; 3 ) = "m4v" or Right ( refPicture2::picture ; 3 ) = "mov"; "height=\"100%\"" ; Right ( refPicture2::picture ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refPicture2::picture ; 3 ) = "pdf" ; "#fff" ; Right ( refPicture2::picture ; 3 ) = "mp4" or Right ( refPicture2::picture ; 3 ) = "m4v" or Right ( refPicture2::picture ; 3 ) = "mov"; "#000" ;"#565e74" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

"<"& FILE_TYPE &";base64," &
B64EncodeFromFM7( refPicture2::picture )&"'\"  "& HEIGHT_WIDTH &"  controls  >" &

"</div></body></html>" ) ;

//-----END






//-----START: Show YouTube Web Media


//------------------------------Test
refPicture2::showMedia[1] ≠ "" and Left ( refPicture2::URL ; 19 ) = "https://www.youtube" ;


//------------------------------Display
refPicture2::URL ;


//-----END






//-----START: Show Other Web Media Info (because file type is unknown)


//------------------------------Test
(
//-----Picture
Right ( refPicture2::URL ; 3 ) = "bmp" or
//EPS images won’t work in web viewer, so display file name instead of file.
//Right ( citationPicture2::URL ; 3 ) = "eps" or
Right ( refPicture2::URL ; 3 ) = "gif" or
Right ( refPicture2::URL ; 4 ) = "jpeg" or
Right ( refPicture2::URL ; 3 ) = "jpg" or
Right ( refPicture2::URL ; 3 ) = "png" or
Right ( refPicture2::URL ; 3 ) = "psd" or
Right ( refPicture2::URL ; 3 ) = "sgi" or
Right ( refPicture2::URL ; 3 ) = "tga" or
Right ( refPicture2::URL ; 3 ) = "tif" or
Right ( refPicture2::URL ; 4 ) = "tiff" or
//-----PDF
Right ( refPicture2::URL ; 3 ) = "pdf" or
//-----Video
Right ( refPicture2::URL ; 3 ) = "mov" or
Right ( refPicture2::URL ; 3 ) = "mp4" or
Right ( refPicture2::URL ; 3 ) = "m4v"
) = 0 and refPicture2::showMedia[1] ≠ "" and Left ( refPicture2::URL ; 19) ≠ "https://www.youtube"
or refPicture2::pictureSourceSpeedLimit = 1;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Substitute ( Substitute (
//Get position of file name’s first letter:
Let ( x = Position ( refPicture2::URL ; "/" ; 1 ; Length ( Filter ( refPicture2::URL ; "/" ) ) ) + 1 ;
//Get position of period after file name’s last letter:
Let ( y = Position ( refPicture2::URL ; "." ; 1 ; Length ( Filter ( refPicture2::URL ; "." ) ) ) ;
//Get file name (letters between last slash and last period:
   Middle ( refPicture2::URL ; x ; y - x ) ) )
//Remove any spaces in the name to keep the name on one line (FileMaker will wrap name to next line if there is a space):
; " " ; "_" ) ; "-" ; "_" ) ;

FILE_TYPE = Let ( x = Position ( refPicture2::URL ; "." ; 1 ; Length ( Filter ( refPicture2::URL ; "." ) ) ) + 1 ;
   Middle ( refPicture2::URL ; x ; 20 ) ) ;

FILE_LOCATION = //Check if URL points to the computer or the web:
Case ( Left ( refPicture2::URL ; 6 ) = "File:/" ;
//Computer:
Let ( p =  refPicture2::URL ;
//Get position of last folder name’s initial slash:
Let ( x = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) - 1 ) ;
//Get position of last folder name’s ending slash:
Let ( y = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) ) ;
//Display folder name:
     "File://... " & Middle ( p ; x ; y - x + 1 ) ) ) ) ;
//Web:
Case ( Middle ( refPicture2::URL ; 8 ; 1 ) = "/" ;
               Left ( refPicture2::URL ; 8 ) ;
               Left ( refPicture2::URL ; 7 ) ) ) ;

MODULE =   "(reference)" ;

MESSAGE =  "Click the 'web' button to view this file." & "<br>" & "<br>" & "This viewer cannot display " & FILE_TYPE & " files (or webpages). It can display " & "<br>" & "bmp, gif, jpeg, jpg, pdf, mov, mp4, m4v, png, psd, sgi,  tga, tif, tiff files," & "<br>" & "and YouTube videos if you have the software installed to view them." & "<br>" & "<br>" & "NOTE: mov files not supported on Windows PCs.  Convert to mp4." ;

BACKGROUND_COLOR = "#fff" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

FILE_NAME &
"<br>" &
FILE_TYPE &
"<br>" &
FILE_LOCATION &
"<br>" &
MODULE &
"<br>" &
"<br>" &
MESSAGE &

"</div></body></html>" ) ;

//-----END






//-----START: Show Other Web Media


//------------------------------Test
refPicture2::showMedia[1] ≠ "" and Left ( refPicture2::URL ; 19) ≠ "https://www.youtube" ;


//------------------------------Variables
Let([
//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refPicture2::URL ; 3 ) = "pdf" ; "#fff" ; Right ( refPicture2::URL ; 3 ) = "mp4" or Right ( refPicture2::URL ; 3 ) = "m4v" or Right ( refPicture2::URL ; 3 ) = "mov"; "#000" ;"#565e74" )  ;

HEIGHT_WIDTH = Case ( Right ( refPicture2::URL ; 3 ) = "mp4" or Right ( refPicture2::URL ; 3 ) = "m4v" or Right ( refPicture2::URL ; 3 ) = "mov";  "height=\"100%\"  width=\"100%\""; Right ( refPicture2::URL ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

URL = Substitute ( refPicture2::URL ; " " ; "%20" ) ;

MEDIA_TYPE =
Case ( Right ( refPicture2::URL ; 3 ) = "mp4" or Right ( refPicture2::URL ; 3 ) = "m4v" or Right ( refPicture2::URL ; 3 ) = "mov";  "video src" ;
Right ( refPicture2::URL ; 3 ) = "pdf"; "object data" ;  "img src" ) ;

CONTROLS = Case ( Right ( refPicture2::URL ; 3 ) = "mp4" or Right ( refPicture2::URL ; 3 ) = "m4v" or Right ( refPicture2::URL ; 3 ) = "mov";  "controls" ; "" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

     "<"& MEDIA_TYPE &"=\"" & URL & "\"  border=\"0\"  "& HEIGHT_WIDTH &"  "& CONTROLS &" >" &

"</div></body></html>" ) ;

//-----END





//-----START: Show HDD Media Info (because file type cannot be displayed by FileMaker)


//------------------------------Test
(
//-----Picture
Right ( refPicture2::fileName ; 3 ) = "bmp" or
//EPS images won’t work in web viewer, so display file name instead of file.
//Right ( citationPicture2::fileName ; 3 ) = "eps" or
Right ( refPicture2::fileName ; 3 ) = "gif" or
Right ( refPicture2::fileName ; 4 ) = "jpeg" or
Right ( refPicture2::fileName ; 3 ) = "jpg" or
Right ( refPicture2::fileName ; 3 ) = "png" or
Right ( refPicture2::fileName ; 3 ) = "psd" or
Right ( refPicture2::fileName ; 3 ) = "sgi" or
Right ( refPicture2::fileName ; 3 ) = "tga" or
Right ( refPicture2::fileName ; 3 ) = "tif" or
Right ( refPicture2::fileName ; 4 ) = "tiff" or
//-----PDF
Right ( refPicture2::fileName ; 3 ) = "pdf" or
//-----Video
Right ( refPicture2::fileName ; 3 ) = "mov" or
Right ( refPicture2::fileName ; 3 ) = "mp4" or
Right ( refPicture2::fileName ; 3 ) = "m4v"
) = 0 and refPicture2::showMedia[2] ≠ "" ;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Substitute ( Substitute (
//Get position of period after file name’s last letter:
Let ( y = Position ( refPicture2::fileName ; "." ; 1 ; Length ( Filter ( refPicture2::fileName ; "." ) ) ) ;
//Get file name (letters between last slash and last period:
   Middle ( refPicture2::fileName ; 1 ; y - 1 ) )
//Remove any spaces in the name to keep the name on one line (FileMaker will wrap name to next line if there is a space):
; " " ; "_" ) ; "-" ; "_" ) ;

FILE_TYPE = Let ( x = Position ( refPicture2::fileName ; "." ; 1 ; Length ( Filter ( refPicture2::fileName ; "." ) ) ) + 1 ;
   Middle ( refPicture2::fileName ; x ; 20 ) ) ;

FILE_LOCATION = Let ( p =  Case (
FilterValues ( refPicture2::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;  Get ( FilePath ) ;

FilterValues ( refPicture2::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ; Get ( FilePath ) & "/x/" ;

FilterValues ( refPicture2::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ; tagPathPicture2_button::tag & "/"  ) ;

//Get position of last folder name’s initial slash:
Let ( x = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) - 1 ) ;
//Get position of last folder name’s ending slash:
Let ( y = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) ) ;
//Display folder name:
     "File://... " & Middle ( p ; x ; y - x + 1 ) ) ) ) ;

MODULE =   "(reference)" ;

MESSAGE =  "Click the 'folder' button to see this file," & "<br>" & "or click 'file' to open it." & "<br>" & "<br>" & "This viewer cannot display " & FILE_TYPE & " files. It can display" & "<br>" & "bmp, gif, jpeg, jpg, pdf, mov, mp4, m4v, png, psd, sgi,  tga, tif," & "<br>" & "and tiff files if you have the software installed to open them." & "<br>" & "<br>" & "NOTE: mov files not supported on Windows PCs.  Convert to mp4." ;

BACKGROUND_COLOR = "#fff" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

FILE_NAME &
"<br>" &
FILE_TYPE &
"<br>" &
FILE_LOCATION &
"<br>" &
MODULE &
"<br>" &
"<br>" &
MESSAGE &

"</div></body></html>" ) ;

//-----END






//-----START:  Show HDD Media


//------------------------------Test
refPicture2::showMedia[2] ≠ "" ;


//------------------------------Variables
Let([
FILE_PATH =
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath)  ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Replace spaces with %20 so will show up on both apple and windows computers:
Substitute (
//Insure file will display on both apple and windows computers:
Case ( Get ( SystemPlatform ) =  - 2 ; "file:" ; "file:/" )  &
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( refPicture2::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;

FilterValues ( refPicture2::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ;

FilterValues ( refPicture2::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
tagPathPicture2_button::tag )
//Close out inquiry:
 ; " " ; "%20" ) & "/" ) );

FILE_NAME = Substitute ( refPicture2::fileName ; " " ; "%20" ) ;

//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refPicture2::fileName ; 3 ) = "pdf" ; "#fff" ; Right ( refPicture2::fileName ; 3 ) = "mp4" or Right ( refPicture2::fileName ; 3 ) = "m4v" or Right ( refPicture2::fileName ; 3 ) = "mov"; "#000" ;"#565e74" )  ;

HEIGHT_WIDTH = Case ( Right ( refPicture2::fileName ; 3 ) = "mp4" or Right ( refPicture2::fileName ; 3 ) = "m4v" or Right ( refPicture2::fileName ; 3 ) = "mov";  "height=\"100%\"  width=\"100%\""; Right ( refPicture2::fileName ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

MEDIA_TYPE = Case ( Right ( refPicture2::fileName ; 3 ) = "mp4" or Right ( refPicture2::fileName ; 3 ) = "m4v" or Right ( refPicture2::fileName ; 3 ) = "mov";  "video src" ; Right ( refPicture2::fileName ; 3 ) = "pdf"; "object data" ;  "img src" ) ;

CONTROLS = Case ( Right ( refPicture2::fileName ; 3 ) = "mp4" or Right ( refPicture2::fileName ; 3 ) = "m4v" or Right ( refPicture2::fileName ; 3 ) = "mov";  "controls" ; "" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\" ><div  align=\"center\"  >" &

     "<"& MEDIA_TYPE &"=\"" & FILE_PATH & FILE_NAME & "\"  border=\"0\"  "& HEIGHT_WIDTH &"  "& CONTROLS &"  >" &

"</div></body></html>" ) ;

//-----END

""   )

//CASE END
