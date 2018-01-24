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

//-----FOR TABLE testlearn

//Show FileMaker container-field contents
//-----START: Show Thumbnail of Image in Container Field
//-----START: Show Container Field File Info
//-----START: Show Container Field PDF or Video Media

//-----FOR TABLE refShowMedia

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


//-----FOR TABLE testlearn


//-----START: Show Thumbnail of Image in Container Field


//------------------------------Test
( (
//-----Picture
Right ( testlearn::picture ; 3 ) = "bmp" or
//EPS doesn’t work!!! Right ( testlearn::picture ; 3 ) = "eps" or
Right ( testlearn::picture ; 3 ) = "gif" or
Right ( testlearn::picture ; 4 ) = "jpeg" or
Right ( testlearn::picture ; 3 ) = "jpg" or
Right ( testlearn::picture ; 3 ) = "png" or
Right ( testlearn::picture ; 3 ) = "psd" or
Right ( testlearn::picture ; 3 ) = "sgi" or
Right ( testlearn::picture ; 3 ) = "tga" or
Right ( testlearn::picture ; 3 ) = "tif" or
Right ( testlearn::picture ; 4 ) = "tiff"
) = 1  and  testlearn::picture ≠ "") and Right ( Get ( FilePath ) ; 3 ) ≠ "fp7" ;


//------------------------------Variables
Let([
BACKGROUND_COLOR = "#565e74" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\”left\”  >" &

"<img src='data:image/jpg;base64," &
B64EncodeFromFM7 ( testlearn::pictureThumbnail ) & "'/  height=\"100%\"  >" &

"</div></body></html>" ) ;

//-----END






//-----START: Show Container Field File Info (because file type cannot be displayed by FileMaker, or file is too large, or both)


//------------------------------Test
( (
//-----Picture
//EPS images can contain characters that base64 can’t read, so display file name instead of file.
//Right ( testlearn::picture ; 3 ) = "eps" or
//-----PDF
Right ( testlearn::picture ; 3 ) = "pdf" or
//-----Video
Right ( testlearn::picture ; 3 ) = "mov" or
Right ( testlearn::picture ; 3 ) = "mp4" or
Right ( testlearn::picture ; 3 ) = "m4v"
) = 0  and  testlearn::picture ≠ "") or
testlearn::picture ≠ "" and Round ( Length ( testlearn::picture ) / 1000000; 2 ) > reference::PictureFileSizeCalc or
testlearn::picture ≠ "" and Right ( Get ( FilePath ) ; 3 ) = "fp7" ;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Let ( x = Length ( GetValue (  testlearn::picture  ; 1 ) ) ;
Substitute ( Substitute ( Case (
Middle ( testlearn::picture ; x - 3 ; 1 ) = "." ;
     Left ( testlearn::picture ; x - 4 ) ;
     Left ( testlearn::picture ; x - 5 ) ) ; " " ; "_" )  ; "-" ; "_" ) ) ;

FILEMAKER_OLDVERSION = Case ( Right ( Get ( FilePath ) ; 3 ) = "fp7" ; "(fp7 can't show container thumbs) " ) ;

FILE_TYPE = Let ( x = Position ( testlearn::picture ; "." ; 1 ; Length ( Filter ( testlearn::picture ; "." ) ) ) + 1 ;
   Middle ( testlearn::picture ; x ; 20 ) ) ;

FILE_SIZE = Let ( x = Length ( testlearn::picture ) ;
Case (
     Round ( x / 1000000; 2 ) < 1 ;
     Middle ( x ; 1 ;3 )  & " KB";
     Round ( x / 1000000; 1 )  & " MB" ) ) ;

MODULE =   "(learn)" ;

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
testlearn::picture ≠ "" ;


//------------------------------Variables
Let([
FILE_TYPE = Case (
//-----PDF
Right ( testlearn::picture ; 3 ) = "pdf"; "object data='data:application/pdf" ;
//-----Video
Right ( testlearn::picture ; 3 ) = "mov"; "video src='data:video/quicktime" ;
Right ( testlearn::picture ; 3 ) = "mp4"; "video src='data:video/mp4" ;
Right ( testlearn::picture ; 3 ) = "m4v"; "video src='data:video/mp4" ;
"unknown" ) ;

HEIGHT_WIDTH = Case ( Right ( testlearn::picture ; 3 ) = "mp4" or Right ( testlearn::picture ; 3 ) = "m4v" or Right ( testlearn::picture ; 3 ) = "mov"; "height=\"100%\"" ; Right ( testlearn::picture ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( testlearn::picture ; 3 ) = "pdf" ; "#fff" ; Right ( testlearn::picture ; 3 ) = "mp4" or Right ( testlearn::picture ; 3 ) = "m4v" or Right ( testlearn::picture ; 3 ) = "mov"; "#000" ;"#565e74" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

"<"& FILE_TYPE &";base64," &
B64EncodeFromFM7( testlearn::picture )&"'\"  "& HEIGHT_WIDTH &"  controls  >" &

"</div></body></html>" ) ;

//-----END






//-----FOR TABLE refShowMedia






//-----START: Show Thumbnail of Image in Container Field


//------------------------------Test
( (
//-----Picture
Right ( refLearnShowMedia::picture ; 3 ) = "bmp" or
//EPS doesn’t work!!! Right ( refShowMedia::picture ; 3 ) = "eps" or
Right ( refLearnShowMedia::picture ; 3 ) = "gif" or
Right ( refLearnShowMedia::picture ; 4 ) = "jpeg" or
Right ( refLearnShowMedia::picture ; 3 ) = "jpg" or
Right ( refLearnShowMedia::picture ; 3 ) = "png" or
Right ( refLearnShowMedia::picture ; 3 ) = "psd" or
Right ( refLearnShowMedia::picture ; 3 ) = "sgi" or
Right ( refLearnShowMedia::picture ; 3 ) = "tga" or
Right ( refLearnShowMedia::picture ; 3 ) = "tif" or
Right ( refLearnShowMedia::picture ; 4 ) = "tiff"
) = 1  and  refLearnShowMedia::picture ≠ "") and Right ( Get ( FilePath ) ; 3 ) ≠ "fp7" ;


//------------------------------Variables
Let([
BACKGROUND_COLOR = "#565e74" ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\”left\”  >" &

"<img src='data:image/jpg;base64," &
B64EncodeFromFM7 ( refLearnShowMedia::pictureThumbnail ) & "'/  height=\"100%\"  >" &

"</div></body></html>" ) ;

//-----END






//-----START: Show Container Field File Info (because file type cannot be displayed by FileMaker, or file is too large, or both)


//------------------------------Test
( (
//-----Picture
//EPS images can contain characters that base64 can’t read, so display file name instead of file.
//Right ( refShowMedia::picture ; 3 ) = "eps" or
//-----PDF
Right ( refLearnShowMedia::picture ; 3 ) = "pdf" or
//-----Video
Right ( refLearnShowMedia::picture ; 3 ) = "mov" or
Right ( refLearnShowMedia::picture ; 3 ) = "mp4" or
Right ( refLearnShowMedia::picture ; 3 ) = "m4v"
) = 0  and  refLearnShowMedia::picture ≠ "") or
refLearnShowMedia::picture ≠ "" and Round ( Length ( refLearnShowMedia::picture ) / 1000000; 2 ) > refLearnShowMedia::PictureFileSizeCalc or
refLearnShowMedia::picture ≠ "" and Right ( Get ( FilePath ) ; 3 ) = "fp7" ;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Let ( x = Length ( GetValue (  refLearnShowMedia::picture  ; 1 ) ) ;
Substitute ( Substitute ( Case (
Middle ( refLearnShowMedia::picture ; x - 3 ; 1 ) = "." ;
     Left ( refLearnShowMedia::picture ; x - 4 ) ;
     Left ( refLearnShowMedia::picture ; x - 5 ) ) ; " " ; "_" )  ; "-" ; "_" ) ) ;

FILEMAKER_OLDVERSION = Case ( Right ( Get ( FilePath ) ; 3 ) = "fp7" ; "(fp7 can't show container thumbs) " ) ;

FILE_TYPE = Let ( x = Position ( refLearnShowMedia::picture ; "." ; 1 ; Length ( Filter ( refLearnShowMedia::picture ; "." ) ) ) + 1 ;
   Middle ( refLearnShowMedia::picture ; x ; 20 ) ) ;

FILE_SIZE = Let ( x = Length ( refLearnShowMedia::picture ) ;
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
refLearnShowMedia::picture ≠ "" ;


//------------------------------Variables
Let([
FILE_TYPE = Case (
//-----PDF
Right ( refLearnShowMedia::picture ; 3 ) = "pdf"; "object data='data:application/pdf" ;
//-----Video
Right ( refLearnShowMedia::picture ; 3 ) = "mov"; "video src='data:video/quicktime" ;
Right ( refLearnShowMedia::picture ; 3 ) = "mp4"; "video src='data:video/mp4" ;
Right ( refLearnShowMedia::picture ; 3 ) = "m4v"; "video src='data:video/mp4" ;
"unknown" ) ;

HEIGHT_WIDTH = Case ( Right ( refLearnShowMedia::picture ; 3 ) = "mp4" or Right ( refLearnShowMedia::picture ; 3 ) = "m4v" or Right ( refLearnShowMedia::picture ; 3 ) = "mov"; "height=\"100%\"" ; Right ( refLearnShowMedia::picture ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refLearnShowMedia::picture ; 3 ) = "pdf" ; "#fff" ; Right ( refLearnShowMedia::picture ; 3 ) = "mp4" or Right ( refLearnShowMedia::picture ; 3 ) = "m4v" or Right ( refLearnShowMedia::picture ; 3 ) = "mov"; "#000" ;"#565e74" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\"><div  align=\"center\"  >" &

"<"& FILE_TYPE &";base64," &
B64EncodeFromFM7( refLearnShowMedia::picture )&"'\"  "& HEIGHT_WIDTH &"  controls  >" &

"</div></body></html>" ) ;

//-----END






//-----START: Show YouTube Web Media


//------------------------------Test
refLearnShowMedia::showMedia[1] ≠ "" and Left ( refLearnShowMedia::URL ; 19 ) = "https://www.youtube" ;


//------------------------------Display
refLearnShowMedia::URL ;


//-----END






//-----START: Show Other Web Media Info (because file type is unknown)


//------------------------------Test
(
//-----Picture
Right ( refLearnShowMedia::URL ; 3 ) = "bmp" or
//EPS images won’t work in web viewer, so display file name instead of file.
//Right ( refShowMedia::URL ; 3 ) = "eps" or
Right ( refLearnShowMedia::URL ; 3 ) = "gif" or
Right ( refLearnShowMedia::URL ; 4 ) = "jpeg" or
Right ( refLearnShowMedia::URL ; 3 ) = "jpg" or
Right ( refLearnShowMedia::URL ; 3 ) = "png" or
Right ( refLearnShowMedia::URL ; 3 ) = "psd" or
Right ( refLearnShowMedia::URL ; 3 ) = "sgi" or
Right ( refLearnShowMedia::URL ; 3 ) = "tga" or
Right ( refLearnShowMedia::URL ; 3 ) = "tif" or
Right ( refLearnShowMedia::URL ; 4 ) = "tiff" or
//-----PDF
Right ( refLearnShowMedia::URL ; 3 ) = "pdf" or
//-----Video
Right ( refLearnShowMedia::URL ; 3 ) = "mov" or
Right ( refLearnShowMedia::URL ; 3 ) = "mp4" or
Right ( refLearnShowMedia::URL ; 3 ) = "m4v"
) = 0 and refLearnShowMedia::showMedia[1] ≠ "" and Left ( refLearnShowMedia::URL ; 19) ≠ "https://www.youtube"
or refLearnShowMedia::pictureSourceSpeedLimit = 1;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Substitute ( Substitute (
//Get position of file name’s first letter:
Let ( x = Position ( refLearnShowMedia::URL ; "/" ; 1 ; Length ( Filter ( refLearnShowMedia::URL ; "/" ) ) ) + 1 ;
//Get position of period after file name’s last letter:
Let ( y = Position ( refLearnShowMedia::URL ; "." ; 1 ; Length ( Filter ( refLearnShowMedia::URL ; "." ) ) ) ;
//Get file name (letters between last slash and last period:
   Middle ( refLearnShowMedia::URL ; x ; y - x ) ) )
//Remove any spaces in the name to keep the name on one line (FileMaker will wrap name to next line if there is a space):
; " " ; "_" ) ; "-" ; "_" ) ;

FILE_TYPE = Let ( x = Position ( refLearnShowMedia::URL ; "." ; 1 ; Length ( Filter ( refLearnShowMedia::URL ; "." ) ) ) + 1 ;
   Middle ( refLearnShowMedia::URL ; x ; 20 ) ) ;

FILE_LOCATION = //Check if URL points to the computer or the web:
Case ( Left ( refLearnShowMedia::URL ; 6 ) = "File:/" ;
//Computer:
Let ( p =  refLearnShowMedia::URL ;
//Get position of last folder name’s initial slash:
Let ( x = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) - 1 ) ;
//Get position of last folder name’s ending slash:
Let ( y = Position ( p ; "/" ; 1 ; Length ( Filter ( p ; "/" ) ) ) ;
//Display folder name:
     "File://... " & Middle ( p ; x ; y - x + 1 ) ) ) ) ;
//Web:
Case ( Middle ( refLearnShowMedia::URL ; 8 ; 1 ) = "/" ;
               Left ( refLearnShowMedia::URL ; 8 ) ;
               Left ( refLearnShowMedia::URL ; 7 ) ) ) ;

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
refLearnShowMedia::showMedia[1] ≠ "" and Left ( refLearnShowMedia::URL ; 19) ≠ "https://www.youtube" ;


//------------------------------Variables
Let([
//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refLearnShowMedia::URL ; 3 ) = "pdf" ; "#fff" ; Right ( refLearnShowMedia::URL ; 3 ) = "mp4" or Right ( refLearnShowMedia::URL ; 3 ) = "m4v" or Right ( refLearnShowMedia::URL ; 3 ) = "mov"; "#000" ;"#565e74" )  ;

HEIGHT_WIDTH = Case ( Right ( refLearnShowMedia::URL ; 3 ) = "mp4" or Right ( refLearnShowMedia::URL ; 3 ) = "m4v" or Right ( refLearnShowMedia::URL ; 3 ) = "mov";  "height=\"100%\"  width=\"100%\""; Right ( refLearnShowMedia::URL ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

URL = Substitute ( refLearnShowMedia::URL ; " " ; "%20" ) ;

MEDIA_TYPE =
Case ( Right ( refLearnShowMedia::URL ; 3 ) = "mp4" or Right ( refLearnShowMedia::URL ; 3 ) = "m4v" or Right ( refLearnShowMedia::URL ; 3 ) = "mov";  "video src" ;
Right ( refLearnShowMedia::URL ; 3 ) = "pdf"; "object data" ;  "img src" ) ;

CONTROLS = Case ( Right ( refLearnShowMedia::URL ; 3 ) = "mp4" or Right ( refLearnShowMedia::URL ; 3 ) = "m4v" or Right ( refLearnShowMedia::URL ; 3 ) = "mov";  "controls" ; "" ) ];


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
Right ( refLearnShowMedia::fileName ; 3 ) = "bmp" or
//EPS images won’t work in web viewer, so display file name instead of file.
//Right ( refShowMedia::fileName ; 3 ) = "eps" or
Right ( refLearnShowMedia::fileName ; 3 ) = "gif" or
Right ( refLearnShowMedia::fileName ; 4 ) = "jpeg" or
Right ( refLearnShowMedia::fileName ; 3 ) = "jpg" or
Right ( refLearnShowMedia::fileName ; 3 ) = "png" or
Right ( refLearnShowMedia::fileName ; 3 ) = "psd" or
Right ( refLearnShowMedia::fileName ; 3 ) = "sgi" or
Right ( refLearnShowMedia::fileName ; 3 ) = "tga" or
Right ( refLearnShowMedia::fileName ; 3 ) = "tif" or
Right ( refLearnShowMedia::fileName ; 4 ) = "tiff" or
//-----PDF
Right ( refLearnShowMedia::fileName ; 3 ) = "pdf" or
//-----Video
Right ( refLearnShowMedia::fileName ; 3 ) = "mov" or
Right ( refLearnShowMedia::fileName ; 3 ) = "mp4" or
Right ( refLearnShowMedia::fileName ; 3 ) = "m4v"
) = 0 and refLearnShowMedia::showMedia[2] ≠ "" ;


//------------------------------Variables
Let([
//Substitute calc replaces spaces and dashes with an underscore to insure filename stays on one line (the first line).  This insures that the file type, size, and module info will be seen by the user.

FILE_NAME = Substitute ( Substitute (
//Get position of period after file name’s last letter:
Let ( y = Position ( refLearnShowMedia::fileName ; "." ; 1 ; Length ( Filter ( refLearnShowMedia::fileName ; "." ) ) ) ;
//Get file name (letters between last slash and last period:
   Middle ( refLearnShowMedia::fileName ; 1 ; y - 1 ) )
//Remove any spaces in the name to keep the name on one line (FileMaker will wrap name to next line if there is a space):
; " " ; "_" ) ; "-" ; "_" ) ;

FILE_TYPE = Let ( x = Position ( refLearnShowMedia::fileName ; "." ; 1 ; Length ( Filter ( refLearnShowMedia::fileName ; "." ) ) ) + 1 ;
   Middle ( refLearnShowMedia::fileName ; x ; 20 ) ) ;

FILE_LOCATION = Let ( p =  Case (
FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;  Get ( FilePath ) ;

FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ; Get ( FilePath ) & "/x/" ;

FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ; tagRefLearnShowMediaFolderPath::tag & "/"  ) ;

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
refLearnShowMedia::showMedia[2] ≠ "" ;


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
FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;

FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ;

FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
tagRefLearnShowMediaFolderPath::tag )
//Close out inquiry:
 ; " " ; "%20" ) & "/" ) );

FILE_NAME = Substitute ( refLearnShowMedia::fileName ; " " ; "%20" ) ;

//Some PDF files have a transparent background which requires white backround in order to show up.  Video files need a black background.  Color background matching module colors is for image files.

BACKGROUND_COLOR =  Case( Right ( refLearnShowMedia::fileName ; 3 ) = "pdf" ; "#fff" ; Right ( refLearnShowMedia::fileName ; 3 ) = "mp4" or Right ( refLearnShowMedia::fileName ; 3 ) = "m4v" or Right ( refLearnShowMedia::fileName ; 3 ) = "mov"; "#000" ;"#565e74" )  ;

HEIGHT_WIDTH = Case ( Right ( refLearnShowMedia::fileName ; 3 ) = "mp4" or Right ( refLearnShowMedia::fileName ; 3 ) = "m4v" or Right ( refLearnShowMedia::fileName ; 3 ) = "mov";  "height=\"100%\"  width=\"100%\""; Right ( refLearnShowMedia::fileName ; 3 ) = "pdf"; "height=\"100%\"  width=\"100%\"" ; "height=\"100%\"" ) ;

MEDIA_TYPE = Case ( Right ( refLearnShowMedia::fileName ; 3 ) = "mp4" or Right ( refLearnShowMedia::fileName ; 3 ) = "m4v" or Right ( refLearnShowMedia::fileName ; 3 ) = "mov";  "video src" ; Right ( refLearnShowMedia::fileName ; 3 ) = "pdf"; "object data" ;  "img src" ) ;

CONTROLS = Case ( Right ( refLearnShowMedia::fileName ; 3 ) = "mp4" or Right ( refLearnShowMedia::fileName ; 3 ) = "m4v" or Right ( refLearnShowMedia::fileName ; 3 ) = "mov";  "controls" ; "" ) ];


//------------------------------Display
"data:text/html," &
"<html><body  bgcolor=\"" & BACKGROUND_COLOR & "\"  LeftMargin=\"0\" RightMargin=\"0\" TopMargin=\"0\" BottomMargin=\"0\" ><div  align=\"center\"  >" &

     "<"& MEDIA_TYPE &"=\"" & FILE_PATH & FILE_NAME & "\"  border=\"0\"  "& HEIGHT_WIDTH &"  "& CONTROLS &"  >" &

"</div></body></html>" ) ;

//-----END

""   )

//CASE END
