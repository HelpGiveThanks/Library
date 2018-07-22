July 20, 2018 17:23:58 Library.fmp12 - showReferencedFileFolder -1-
learn: showReferencedFileFolder
#
#
#FILE BUTTON (or on copyright menu WEB BUTTON)
#See if there is a file or folder to show the user.
If [ $$openReferencedWebsite = "" ]
If [ ( Get (LayoutTableName) = "reference" and
 (
//All fields required to find file in the main or x folders.
reference::fileName ≠ "" and reference::kfileLocation ≠ "" and FilterValues ( reference::kfileLocation ; "8162011225605315" )
≠ "8162011225605315" & ¶
 or
//All fields required to a find file in a file path tag 'other' folder.
reference::fileName ≠ "" and reference::kfileLocation ≠ "" and reference::kfolderpath ≠ ""
 ) ) = 0
and
( Get (LayoutTableName) = "tagMenus" and
 (
//All fields required to find file in the main or x folders.
$$tagMenusFileName ≠ "" and $$tagMenusFileLocation ≠ "" and FilterValues ( $$tagMenusFileLocation ;
"8162011225605315" ) ≠ "8162011225605315" & ¶
 or
//All fields required to a find file in a file path tag 'other' folder.
$$tagMenusFileName ≠ "" and $$tagMenusFileLocation ≠ "" and $$tagMenusFilePath ≠ ""
 or
//URL field is empty.
$$tagMenusURL ≠ ""
 ) ) = 0
and
( Get (LayoutTableName) = "testlearn" and
 (
//Check if first reference record has media to show and that the user has not decided to show reference media.
Case ( testlearn::kshowReferencedMedia = "" ;
//All fields required to find file in the main or x folders.
refLearn::fileName ≠ "" and refLearn::kfileLocation ≠ "" and FilterValues ( refLearn::kfileLocation ; "8162011225605315" ) ≠
"8162011225605315" & ¶
 or
//All fields required to find a file in a file path tag 'other' folder.
refLearn::fileName ≠ "" and refLearn::kfileLocation ≠ "" and refLearn::kfolderpath ≠ "" )
or
//Check if the user has decided to show reference media.
Case ( testlearn::kshowReferencedMedia ≠ "" ;
//All fields required to find file in the main or x folders.
refLearnShowMedia::fileName ≠ "" and refLearnShowMedia::kfileLocation ≠ "" and FilterValues ( refLearnShowMedia::
kfileLocation ; "8162011225605315" ) ≠ "8162011225605315" & ¶
 or
//All fields required to find a file in a file path tag 'other' folder.
refLearnShowMedia::fileName ≠ "" and refLearnShowMedia::kfileLocation ≠ "" and refLearnShowMedia::kfolderpath ≠ "" )
) ) = 0
and
( Get (LayoutTableName) = "testlearnReportTags" and
 (
//Check if first reference record has media to show and that the user has not decided to show reference media.
Case ( testlearnReportTags::kshowReferencedMedia = "" ;
//All fields required to find file in the main or x folders.
refTest::fileName ≠ "" and refTest::kfileLocation ≠ "" and FilterValues ( refTest::kfileLocation ; "8162011225605315" ) ≠
"8162011225605315" & ¶
 or
//All fields required to find a file in a file path tag 'other' folder.
refTest::fileName ≠ "" and refTest::kfileLocation ≠ "" and refTest::kfolderpath ≠ "" )
or
//Check if the user has decided to show reference media.
Case ( testlearnReportTags::kshowReferencedMedia ≠ "" ;
//All fields required to find file in the main or x folders.
refTestShowMedia::fileName ≠ "" and refTestShowMedia::kfileLocation ≠ "" and FilterValues ( refTestShowMedia::
kfileLocation ; "8162011225605315" ) ≠ "8162011225605315" & ¶
 or
//All fields required to find a file in a file path tag 'other' folder.
refTestShowMedia::fileName ≠ "" and refTestShowMedia::kfileLocation ≠ "" and refTestShowMedia::kfolderpath ≠ "" )
) ) = 0 ]
#
#Stop script if the record has no file to open or
#it does, but the user has not yet entered all the
#information required to open this file.
Exit Script [ ]
End If
End If
#
#
#WEB BUTTON
#See if there is a website to show the user.
If [ $$openReferencedWebsite = 1 ]
#
#A return of zero for all calc's means the
#current learn record has zero references
#with its website/URL field filled in.
If [ //Test to see if any reference on all layouts where they can appear has a website that can be opened.
(
 reference::URL ≠ "" or
 reference::ISBN ≠ "" or
 reference::ISSN ≠ "" or
 reference::DOI ≠ "" or
//DO NOT TEST TagMenus (there is only one button for website, file, and folder)
 Case ( testlearn::kshowReferencedMedia = "" ;
 refLearn::URL ≠ "" or
 refLearn::ISBN ≠ "" or
 refLearn::ISSN ≠ "" or
 refLearn::DOI ≠ ""
 ;
 refLearnShowMedia::URL ≠ "" or
 refLearnShowMedia::ISBN ≠ "" or
 refLearnShowMedia::ISSN ≠ "" or
 refLearnShowMedia::DOI ≠ ""
 ) or
 Case ( testlearnReportTags::kshowReferencedMedia = "" ;
 refTest::URL ≠ "" or
 refTest::ISBN ≠ "" or
 refTest::ISSN ≠ "" or
 refTest::DOI ≠ ""
 ;
 refTestShowMedia::URL ≠ "" or
 refTestShowMedia::ISBN ≠ "" or
 refTestShowMedia::ISSN ≠ "" or
 refTestShowMedia::DOI ≠ ""
 )
) = 0 ]
#
#Stop the script if there is website url to open.
Set Variable [ $$openReferencedWebsite ]
Exit Script [ ]
End If
#
#If there is a website to open, then note this for
#calcs below so the website opening calc will
#be used.
Set Variable [ $openReferencedWebsite; Value:1 ]
Set Variable [ $$openReferencedWebsite ]
End If
#
#
#FILE BUTTON
#If the user clicked a file button
#the present them with
#file and folder buttons.
If [ $openReferencedWebsite = "" ]
#
#If the file path tag's "real shelf, box, etc."
#checkbox in the Reference's Tag Menu's
#window is empty, then ask if the user wants to
#open the digital-file's folder or open the file.
If [ tagRefFolderPath::kfileORkTestItemCreatorNode = "" and tagRefLearnFolderPath::kfileORkTestItemCreatorNode = "" and
refTestFolderPath::kfileORkTestItemCreatorNode = "" and $$tagMenusRealCheckbox = "" ]
#
Show Custom Dialog [ Message: "Open the file's folder" & ¶ & "OR" & ¶ & "the file?"; Default Button: “file”, Commit: “Yes”;
Button 2: “folder”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
Else
#If "real shelf, box, etc." is checked, then show
#the comment below to guide user to the
#object's (not digital file's) physical location.
If [ Get (LayoutTableName) = "reference" ]
Show Custom Dialog [ Message: "Located: " & tagRefFolderPath::tag & " >>> " & Case ( reference::fileName ≠ "" ;
reference::fileName ); Default Button: “OK”, Commit: “Yes” ]
Else If [ Get (LayoutTableName) = "testlearn" ]
Show Custom Dialog [ Message: "Located: " & tagRefLearnFolderPath::tag & " >>> " & Case ( refLearn::fileName ≠ "" ;
refLearn::fileName ); Default Button: “OK”, Commit: “Yes” ]
Else If [ Get (LayoutTableName) = "tagMenus" ]
Show Custom Dialog [ Message: "Located: " & $$tagMenusFilePath & " >>> " & Case ( $$tagMenusFileName ≠ "" ; $
$tagMenusFileName ); Default Button: “OK”, Commit: “Yes” ]
Else If [ Get (LayoutTableName) = "testlearnReportTags" ]
#The picture window that opens on the test and
#report module layouts is for the testlearn
#table, so no special message is required.
End If
Exit Script [ ]
End If
End If
#
#
#If the user selects to open the file's folder
#instead of the file, then note this for calcs
#below so the folder opening calc will be used.
If [ Get ( LastMessageChoice ) = 2 ]
#
Set Variable [ $openFolder; Value:1 ]
#
#Show file name and folder path before
#opening it ...
#
#... on reference layouts.
If [ Get (LayoutTableName) = "reference" ]
Show Custom Dialog [ Message: "The folder that — " & reference::fileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
tagRefFolderPath::tag ); Default Button: “OK”, Commit: “Yes” ]
End If
#
#... on tagMenus layouts.
If [ Get (LayoutTableName) = "tagMenus" ]
Show Custom Dialog [ Message: "The folder that — " & $$tagMenusFileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( $$tagMenusFileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( $$tagMenusFileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( $$tagMenusFileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
$$tagMenusFilePath ); Default Button: “OK”, Commit: “Yes” ]
End If
#
#... on learn layouts.
If [ Get (LayoutTableName) = "testlearn" ]
If [ testlearn::kshowReferencedMedia ≠ "" ]
Show Custom Dialog [ Message: "The folder that — " & refLearn::fileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
tagRefLearnFolderPath::tag ); Default Button: “OK”, Commit: “Yes” ]
Else If [ testlearn::kshowReferencedMedia = "" ]
Show Custom Dialog [ Message: "The folder that — " & refLearn::fileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( refLearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( refLearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( refLearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
tagRefLearnFolderPath::tag ); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#... on test and report layouts.
If [ Get ( LayoutTableName ) = "testlearnReportTags" ]
If [ testlearnReportTags::kshowReferencedMedia ≠ "" ]
Show Custom Dialog [ Message: "The folder that — " & refTestShowMedia::fileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( refTestShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( refTestShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( refTestShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
refTestFolderPath::tag ); Default Button: “OK”, Commit: “Yes” ]
Else If [ testlearnReportTags::kshowReferencedMedia = "" ]
Show Custom Dialog [ Message: "The folder that — " & refTest::fileName & " — is in will now open >>> " &
Replace (
//Get position of first slash = file path info common to both apple and windows computers:
Let ( x = Position ( Get ( FilePath ) ; "/" ; 1 ; 1 ) ;
//Get position of last slash = end of file path (or start of filename):
Let ( y = Position ( Get (FilePath) ; "/" ; 1 ; Length ( Filter ( Get (FilePath) ; "/" ) ) ) ;
//Get file path (three possible paths: Main, X, and Other)
Case (
FilterValues ( refTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) ;
FilterValues ( refTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ;
Middle ( Get ( FilePath ) ; x ; y - x ) & "/x" ) ) )
; 1 ; 1 ; "" )
 &
Case ( FilterValues ( refTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ;
refTestFolderPath::tag ); Default Button: “OK”, Commit: “Yes” ]
End If
End If
End If
#
#
#
#Proceed to opening website, file, or folder.
#
#
#
#BEGIN: REFERENCE LAYOUTS
If [ Get ( LayoutTableName ) = "reference" ]
#
#
#
#Open website if user clicked 'web'.
If [ $openReferencedWebsite = 1 ]
Open URL [ Case ( reference::URL ≠ "" ; reference::URL ;
reference::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & reference::ISBN ;
reference::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & reference::ISSN ;
reference::DOI ≠ "" ; "http://dx.doi.org/" & reference::DOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( reference::URL ≠ "" ; reference::URL ;
reference::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & reference::ISBN ;
reference::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & reference::ISSN ;
reference::DOI ≠ "" ; "http://dx.doi.org/" & reference::DOI ) & " Make a temporary change and try again?"; Default
Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( reference::URL ≠ "" ; reference::URL ;
reference::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & reference::ISBN ;
reference::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & reference::ISSN ;
reference::DOI ≠ "" ; "http://dx.doi.org/" & reference::DOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( reference::URL ≠ "" ; reference::URL ;
reference::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & reference::ISBN ;
reference::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & reference::ISSN ;
reference::DOI ≠ "" ; "http://dx.doi.org/" & reference::DOI ) & " Try again?"; Default Button: “OK”, Commit:
“Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
End If
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( reference::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & reference::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & reference::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & reference::fileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( reference::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & reference::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & reference::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & reference::fileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( reference::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; "%20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefFolderPath::tag ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( reference::fileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; " " ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefFolderPath::tag ; 1 ) = "/" ; Substitute ( reference::fileName ; " " ; " " ) ;
 "/" & Substitute ( reference::fileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefFolderPath::tag ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( tagRefFolderPath::tag ) & ", OR this path tag is invalid, OR
the file name is no longer " & reference::fileName & "."
;
Case ( Get ( WindowName ) = "Tag Menus" and $$citationMatch ≠ "cite" ;
"This folder-path tag" & Quote ( tagRefFolderPath::tag ) & " is a not working. 1) Go to the Reference section 2) Tag
Menu 3) path menu to fix it."
 ;
"This folder-path tag" & Quote ( tagRefFolderPath::tag ) & " is a not working. 1) Go to the Tag Menu 2) path menu
to fix it."
 )
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#
End If
#END: REFERENCE LAYOUTS
#
#
#
#
#
#
#BEGIN: TAGMENUS LAYOUTS
If [ Get ( LayoutTableName ) = "tagMenus" ]
#
#
#
#Open website if user clicked 'web'.
If [ $openReferencedWebsite = 1 ]
Open URL [ Case ( $$tagMenusURL ≠ "" ; $$tagMenusURL ;
$$tagMenusISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & $$tagMenusISBN ;
$$tagMenusISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & $$tagMenusISSN ;
$$tagMenusDOI ≠ "" ; "http://dx.doi.org/" & $$tagMenusDOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( $$tagMenusURL ≠ "" ; $$tagMenusURL ;
$$tagMenusISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & $$tagMenusISBN ;
$$tagMenusISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & $$tagMenusISSN ;
$$tagMenusDOI ≠ "" ; "http://dx.doi.org/" & $$tagMenusDOI ) & " Make a temporary change and try again?";
Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( $$tagMenusURL ≠ "" ; $$tagMenusURL ;
$$tagMenusISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & $$tagMenusISBN ;
$$tagMenusISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & $$tagMenusISSN ;
$$tagMenusDOI ≠ "" ; "http://dx.doi.org/" & $$tagMenusDOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( $$tagMenusURL ≠ "" ; $$tagMenusURL ;
$$tagMenusISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & $$tagMenusISBN ;
$$tagMenusISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & $$tagMenusISSN ;
$$tagMenusDOI ≠ "" ; "http://dx.doi.org/" & $$tagMenusDOI ) & " Try again?"; Default Button: “OK”,
Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
End If
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( $$tagMenusFileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & $$tagMenusFileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & $$tagMenusFileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & $$tagMenusFileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( $$tagMenusFileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & $$tagMenusFileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & $$tagMenusFileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & $$tagMenusFileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( $$tagMenusFileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & $$tagMenusFilePath ; " " ; "%20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( $$tagMenusFilePath ; 1 ) = "/" ; Substitute ( $$tagMenusFileName ; " " ; "%20" ) ;
 "/" & Substitute ( $$tagMenusFileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & $$tagMenusFilePath ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & $$tagMenusFilePath ; " " ; " " ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( $$tagMenusFilePath ; 1 ) = "/" ; Substitute ( $$tagMenusFileName ; " " ; " " ) ;
 "/" & Substitute ( $$tagMenusFileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & $$tagMenusFilePath ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( $$tagMenusFilePath ) & ", OR this path tag is invalid, OR the
file name is no longer " & $$tagMenusFileName & "."
;
Case ( Get ( WindowName ) = "Tag Menus" and $$citationMatch ≠ "cite" ;
"This folder-path tag" & Quote ( $$tagMenusFilePath ) & " is a not working. 1) Go to the Reference section 2) Tag
Menu 3) path menu to fix it."
 ;
"This folder-path tag" & Quote ( $$tagMenusFilePath ) & " is a not working. 1) Go to the Tag Menu 2) path menu to
fix it."
 )
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#
End If
#END: TAGMENUS LAYOUTS
#
#
#
#
#
#
#BEGIN: LEARN LAYOUTS
If [ Get ( LayoutTableName ) = "testlearn" ]
#
#
#
#If there is more than one reference record
#tagged to this Learn window record, tell the
#how to see the rest.
If [ ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) > 1 ]
If [ $openFolder = "" ]
If [ $openReferencedWebsite = "" ]
#If the user selected to open a file,
#show this message.
Show Custom Dialog [ Message: "The first referenced file tagged to this Learn record will now open. To see all —
" & ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) & " — references
tagged to it, 1) click the 'QV' button in the Learn window, or the 'references' button in the Tag Menus window,
2) and scroll down to see the tagged references."; Default Button: “OK”, Commit: “Yes” ]
Else
#If the user selected to open a website,
#show this message.
Show Custom Dialog [ Message: "The first referenced website tagged to this Learn record will now open. To see
all — " & ValueCount ( testlearn::kcreference ) - Length ( Filter ( testlearn::kcreference ; "L" ) ) & " —
references tagged to it, 1) click the 'QV' button in the Learn window, or the 'references' button in the Tag
Menus window, 2) and scroll down to see the tagged references."; Default Button: “OK”, Commit: “Yes” ]
End If
Else
#If the user selected to open a folder,
#show this message.
Show Custom Dialog [ Message: "FYI: This is the first of — " & ValueCount ( testlearn::kcreference ) - Length ( Filter
( testlearn::kcreference ; "L" ) ) & " — references tagged to this record. Click the 'QV' button in the Learn window,
or the 'references' button in the Tag Menus window, to view them all."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#
#Open website if user clicked 'web'.
#
#Media file reference selected.
If [ $openReferencedWebsite = 1 and testlearn::kshowReferencedMedia ≠ "" ]
Open URL [ Case ( refLearnShowMedia::URL ≠ "" ; refLearnShowMedia::URL ;
refLearnShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearnShowMedia::ISBN ;
refLearnShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearnShowMedia::ISSN ;
refLearnShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refLearnShowMedia::DOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( refLearnShowMedia::URL ≠ "" ; refLearnShowMedia::URL ;
refLearnShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearnShowMedia::ISBN ;
refLearnShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearnShowMedia::ISSN ;
refLearnShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refLearnShowMedia::DOI ) & " Make a temporary change and
try again?"; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( refLearnShowMedia::URL ≠ "" ; refLearnShowMedia::URL ;
refLearnShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearnShowMedia::ISBN ;
refLearnShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearnShowMedia::ISSN ;
refLearnShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refLearnShowMedia::DOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( refLearnShowMedia::URL ≠ "" ; refLearnShowMedia::URL ;
refLearnShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearnShowMedia::
ISBN ;
refLearnShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearnShowMedia::ISSN ;
refLearnShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refLearnShowMedia::DOI ) & " Try again?"; Default
Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
#
#
#Media file reference is not selected, so first
#reference record's web file will be shown.
Else If [ $openReferencedWebsite = 1 and testlearn::kshowReferencedMedia = "" ]
Open URL [ Case ( refLearn::URL ≠ "" ; refLearn::URL ;
refLearn::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearn::ISBN ;
refLearn::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearn::ISSN ;
refLearn::DOI ≠ "" ; "http://dx.doi.org/" & refLearn::DOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( refLearn::URL ≠ "" ; refLearn::URL ;
refLearn::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearn::ISBN ;
refLearn::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearn::ISSN ;
refLearn::DOI ≠ "" ; "http://dx.doi.org/" & refLearn::DOI ) & " Make a temporary change and try again?"; Default
Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( refLearn::URL ≠ "" ; refLearn::URL ;
refLearn::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearn::ISBN ;
refLearn::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearn::ISSN ;
refLearn::DOI ≠ "" ; "http://dx.doi.org/" & refLearn::DOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( refLearn::URL ≠ "" ; refLearn::URL ;
refLearn::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refLearn::ISBN ;
refLearn::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refLearn::ISSN ;
refLearn::DOI ≠ "" ; "http://dx.doi.org/" & refLearn::DOI ) & " Try again?"; Default Button: “OK”, Commit:
“Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
End If
#
#
#
#BEGIN: Show selected reference media file ...
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refLearnShowMedia::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes try %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refLearnShowMedia::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & refLearnShowMedia::fileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refLearnShowMedia::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refLearnShowMedia::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & refLearnShowMedia::fileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( refLearnShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnShowMediaFolderPath::tag ; " " ; "%
20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefLearnShowMediaFolderPath::tag ; 1 ) = "/" ; Substitute ( refLearnShowMedia::fileName ; " " ; "%
20" ) ;
 "/" & Substitute ( refLearnShowMedia::fileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnShowMediaFolderPath::tag ; " " ; "%
20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnShowMediaFolderPath::tag ; " " ; "
" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefLearnShowMediaFolderPath::tag ; 1 ) = "/" ; Substitute ( refLearnShowMedia::fileName ; " " ; "
" ) ;
 "/" & Substitute ( refLearnShowMedia::fileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnShowMediaFolderPath::tag ; " " ; "
" )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( tagRefLearnShowMediaFolderPath::tag ) & ", OR this path
tag is invalid, OR the file name is no longer " & refLearnShowMedia::fileName & "."
;
"This folder-path tag" & Quote ( tagRefLearnShowMediaFolderPath::tag ) & " is a not working. 1) Go to the
Reference section 2) Tag Menu 3) path menu to fix it."
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#END: Show selected reference media file ...
#
#
#
#BEGIN: Show first reference file in QV list ...
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( refLearn::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ and testlearn::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refLearn::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refLearn::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & refLearn::fileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( refLearn::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ and testlearn::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refLearn::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refLearn::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & refLearn::fileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( refLearn::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and testlearn::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnFolderPath::tag ; " " ; "%20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefLearnFolderPath::tag ; 1 ) = "/" ; Substitute ( refLearn::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( refLearn::fileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnFolderPath::tag ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnFolderPath::tag ; " " ; " " ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( tagRefLearnFolderPath::tag ; 1 ) = "/" ; Substitute ( refLearn::fileName ; " " ; " " ) ;
 "/" & Substitute ( refLearn::fileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagRefLearnFolderPath::tag ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( tagRefLearnFolderPath::tag ) & ", OR this path tag is invalid,
OR the file name is no longer " & refLearn::fileName & "."
;
"This folder-path tag" & Quote ( tagRefLearnFolderPath::tag ) & " is a not working. 1) Go to the Reference section
2) Tag Menu 3) path menu to fix it."
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#END: Show first reference file in QV list ...
#
#
#
End If
#END: LEARN LAYOUTS
#
#
#
#
#
#
#BEGIN: TEST AND REPORT LAYOUTS
If [ Get ( LayoutTableName ) = "testlearnReportTags" ]
#
#
#
#If there is more than one reference record
#tagged to this testlearn record, then tell user
#how to see and open them ...
If [ ValueCount ( testlearnReportTags::kcreference ) - Length ( Filter ( testlearnReportTags::kcreference ; "L" ) ) > 1 ]
If [ $openFolder = "" ]
If [ $openReferencedWebsite = "" ]
#If the user selected to open a file,
#show this message.
Show Custom Dialog [ Message: "The first referenced file tagged to this Learn record will now open. To see all —
" & ValueCount ( testlearnReportTags::kcreference ) - Length ( Filter ( testlearnReportTags::kcreference ;
"L" ) ) & " — references tagged to it, 1) click the 'QV' button in the Learn window, or the 'references' button in
the Tag Menus window, 2) and scroll down to see the tagged references."; Default Button: “OK”, Commit:
“Yes” ]
Else
#If the user selected to open a website,
#show this message.
Show Custom Dialog [ Message: "The first referenced website tagged to this Learn record will now open. To see
all — " & ValueCount ( testlearnReportTags::kcreference ) - Length ( Filter ( testlearnReportTags::
kcreference ; "L" ) ) & " — testlearnReportTags tagged to it, 1) click the 'QV' button in the Learn window, or the
'references' button in the Tag Menus window, 2) and scroll down to see the tagged references."; Default
Button: “OK”, Commit: “Yes” ]
End If
Else
#If the user selected to open a folder,
#show this message.
Show Custom Dialog [ Message: "FYI: This is the first of — " & ValueCount ( testlearnReportTags::kcreference ) -
Length ( Filter ( testlearnReportTags::kcreference ; "L" ) ) & " — references tagged to this record. 1) Click the 'QV'
button in the Learn window, or the 'references' button in the Tag Menus window, 2) and scroll down to see the
tagged references."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#
#Open website if user clicked 'web'.
#
#Media file reference selected.
If [ $openReferencedWebsite = 1 and testlearnReportTags::kshowReferencedMedia ≠ "" ]
Open URL [ Case ( refTestShowMedia::URL ≠ "" ; refTestShowMedia::URL ;
refTestShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTestShowMedia::ISBN ;
refTestShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTestShowMedia::ISSN ;
refTestShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refTestShowMedia::DOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( refTestShowMedia::URL ≠ "" ; refTestShowMedia::URL ;
refTestShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTestShowMedia::ISBN ;
refTestShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTestShowMedia::ISSN ;
refTestShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refTestShowMedia::DOI ) & " Make a temporary change and try
again?"; Default Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( refTestShowMedia::URL ≠ "" ; refTestShowMedia::URL ;
refTestShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTestShowMedia::ISBN ;
refTestShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTestShowMedia::ISSN ;
refTestShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refTestShowMedia::DOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( refTestShowMedia::URL ≠ "" ; refTestShowMedia::URL ;
refTestShowMedia::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTestShowMedia::ISBN ;
refTestShowMedia::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTestShowMedia::ISSN ;
refTestShowMedia::DOI ≠ "" ; "http://dx.doi.org/" & refTestShowMedia::DOI ) & " Try again?"; Default
Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
#
#
#Media file reference is not selected, so first
#reference record's web file will be shown.
Else If [ $openReferencedWebsite = 1 and testlearnReportTags::kshowReferencedMedia = "" ]
Open URL [ Case ( refTest::URL ≠ "" ; refTest::URL ;
refTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTest::ISBN ;
refTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTest::ISSN ;
refTest::DOI ≠ "" ; "http://dx.doi.org/" & refTest::DOI ) ]
[ No dialog ]
#
#If the web address fails let user know and
#allow them to modify url and try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "The reference's web address (URL) is not working: " &
Case ( refTest::URL ≠ "" ; refTest::URL ;
refTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTest::ISBN ;
refTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTest::ISSN ;
refTest::DOI ≠ "" ; "http://dx.doi.org/" & refTest::DOI ) & " Make a temporary change and try again?"; Default
Button: “OK”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
#If user cancels, then exit this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#If user wants to try again, let them.
Loop
Allow User Abort [ Off ]
Set Error Capture [ On ]
Open URL [ Case ( refTest::URL ≠ "" ; refTest::URL ;
refTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTest::ISBN ;
refTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTest::ISSN ;
refTest::DOI ≠ "" ; "http://dx.doi.org/" & refTest::DOI ) ]
#
#Exit script if website opens.
Exit Loop If [ Get ( LastError ) = 0 ]
#
#If it fails, ask the user if they want to try again.
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This change to reference's web address (URL) failed: " &
Case ( refTest::URL ≠ "" ; refTest::URL ;
refTest::ISBN ≠ "" ; "http://www.worldcat.org/search?q=bn%3A" & refTest::ISBN ;
refTest::ISSN ≠ "" ; "http://www.worldcat.org/ISSN/" & refTest::ISSN ;
refTest::DOI ≠ "" ; "http://dx.doi.org/" & refTest::DOI ) & " Try again?"; Default Button: “OK”, Commit:
“Yes”; Button 2: “cancel”, Commit: “No” ]
End If
#
#Exit script if user cancels. There are two dialog
#boxes in which the user can cancel: the above
#comment and the above Open Url dialog box.
Exit Loop If [ Get ( LastMessageChoice ) = 2 or Get ( LastError ) = 1 ]
End Loop
End If
Exit Script [ ]
End If
#
#
#
#BEGIN: Show selected reference media file ...
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( refTestShowMedia::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refTestShowMedia::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refTestShowMedia::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & refTestShowMedia::fileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( refTestShowMedia::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refTestShowMedia::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refTestShowMedia::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & refTestShowMedia::fileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( refTestShowMedia::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestShowMediaFolderPath::tag ; " " ; "%20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( refTestShowMediaFolderPath::tag ; 1 ) = "/" ; Substitute ( refTestShowMedia::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( refTestShowMedia::fileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestShowMediaFolderPath::tag ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestShowMediaFolderPath::tag ; " " ; " " ) &
Case ( Right ( refTestShowMediaFolderPath::tag ; 1 ) = "/" ; Substitute ( refTestShowMedia::fileName ; " " ; " " ) ;
 "/" & Substitute ( refTestShowMedia::fileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestShowMediaFolderPath::tag ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( refTestShowMediaFolderPath::tag ) & ", OR this path tag is
invalid, OR the file name is no longer " & refTestShowMedia::fileName & "."
;
Case ( Get ( WindowName ) = "Tag Menus" ;
"This folder-path tag" & Quote ( refTestShowMediaFolderPath::tag ) & " is a not working. 1) Go to the Reference
section 2) Tag Menu 3) path menu to fix it."
 ;
"This folder-path tag" & Quote ( refTestShowMediaFolderPath::tag ) & " is a not working. 1) Go to the Tag Menu 2)
path menu to fix it."
 )
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#END: Show selected reference media file ...
#
#
#
#BEGIN: Show first reference file in QV list ...
#
#
#
#Show file in or open ...
#
#... folder x.
If [ FilterValues ( refTest::kfileLocation ; "8162011225532313" ) = "8162011225532313" & ¶ and testlearnReportTags::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refTest::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" & refTest::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/" ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's x folder, OR its name is no
longer " & refTest::fileName & "."
;
"The x folder has been moved, deleted, or perhaps never created (something the user must do during setup). The
library's x folder needs to be here " & Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get
( FilePath ) ; 6 ; Length ( Get (FilePath ) ) - Length ( Get (FileName ) ) - 11) & "x/"
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... main library folder.
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225558314" ) = "8162011225558314" & ¶ and testlearnReportTags::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refTest::fileName ; " " ; "%20" )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) & refTest::fileName ; " " ; " " )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:" ; "file:/" ) & Middle ( Get ( FilePath ) ; 6 ; Length ( Get
(FilePath ) ) - Length ( Get (FileName ) ) - 11) ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted, moved from, or never downloaded/moved into this library's main folder, OR its name is
no longer " & refTest::fileName & "."
;
//Since the main folder's file path is the same as the library's it will never fail to open. So a failure message is not
needed.
); Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
#
#... other folder defined by a folder path tag.
Else If [ FilterValues ( refTest::kfileLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and testlearnReportTags::
kshowReferencedMedia = "" ]
#Use %20 space substitutes.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; "%20" ) &
//Check if file path tag ends in forward slash. If it does NOT, add one.
Case ( Right ( refTestFolderPath::tag ; 1 ) = "/" ; Substitute ( refTest::fileName ; " " ; "%20" ) ;
 "/" & Substitute ( refTest::fileName ; " " ; "%20" ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; "%20" )
) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Case ( $openFolder = "" ;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; " " ) &
Case ( Right ( refTestFolderPath::tag ; 1 ) = "/" ; Substitute ( refTest::fileName ; " " ; " " ) ;
 "/" & Substitute ( refTest::fileName ; " " ; " " ) )
;
Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & refTestFolderPath::tag ; " " ; " " )
) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: Case ( $openFolder = "" ;
"The file has been deleted or moved from " & Quote ( refTestFolderPath::tag ) & ", OR this path tag is invalid, OR
the file name is no longer " & refTest::fileName & "."
;
Case ( Get ( WindowName ) = "Tag Menus" ;
"This folder-path tag" & Quote ( refTestFolderPath::tag ) & " is a not working. 1) Go to the Reference section 2)
Tag Menu 3) path menu to fix it."
 ;
"This folder-path tag" & Quote ( refTestFolderPath::tag ) & " is a not working. 1) Go to the Tag Menu 2) path menu
to fix it."
 )
); Default Button: “OK”, Commit: “Yes” ]
End If
End If
#END: Show first reference file in QV list ...
#
#
#
End If
#END: TEST AND REPORT LAYOUTS
#
#
