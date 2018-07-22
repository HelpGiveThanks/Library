July 20, 2018 21:31:34 Library.fmp12 - CHUNK_insertPictureOrMovie -1-
pictures: CHUNK_insertPictureOrMovie
#
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#If converting from fp7, replace unknown
#fields below as noted below. Also update all
#FileInsert script steps as noted below.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Tranfer the global variables to local variables
#and then clear the globals. This way these
#needed variables don't need to be cleared
#before every exit step in this script, as local
#variables expire as soon as the script exits.
Set Variable [ $picture; Value:$$picture ]
Set Variable [ $reportTable; Value:$$reportTable ]
Set Variable [ $fileLocation; Value:$$fileLocation ]
Set Variable [ $learnLayout; Value:$$learnLayout ]
Set Variable [ $referenceLayout; Value:$$referenceLayout ]
#
Set Variable [ $$picture ]
Set Variable [ $$reportTable ]
Set Variable [ $$fileLocation ]
Set Variable [ $$learnLayout ]
Set Variable [ $$referenceLayout ]
#
#
#If the user is replacing media, then the Media
#window will already be open, and the script
#needs to know what table media is going into.
If [ Get ( WindowName ) = "Media" ]
#
#If user is on a reference layout...
If [ Get (LayoutTableName) = "reference" ]
Set Variable [ $referenceLayout; Value:1 ]
#
#If user is on a learn layout...
Else If [ Get (LayoutTableName) = "testLearn"
 or
Get (LayoutTableName) = "testLearnReportTags" ]
Set Variable [ $learnLayout; Value:1 ]
End If
#
End If
#
#
#------------------------
#
#
#BEGIN: iDevice
#
#
#If the user in on an iDevice...
If [ Get ( SystemPlatform ) = 3 ]
#
#
#
#NOTE: This sequence of questions may seem
#to be in reverse order, however, FileMaker
#displays sequences of buttons from
#right-to-left instead of left-to-right, so
#LastMessageChoice 1 = right,
#2 = middle, and 3 = left button, thus for the
#dialogue box the user sees we have to deal
#here in reverse order so it reads left to right for
#the user.
#
#
#
#Ask user if they want to
# A) get media from an iDevice's library,
# B) create new media with the camera,
# C) or cancel.
Show Custom Dialog [ Message: "Get a picture, or movie, from your device's media library; or use its camera to take a picture, or
make a movie?"; Default Button: “cancel”, Commit: “Yes”; Button 2: “camera”, Commit: “No”; Button 3: “library”, Commit:
“No” ]
#
#
#
#BEGIN Answer C (cancel)
#
#
#
#C) If the user cancels, then exit the script.
If [ Get ( LastMessageChoice ) = 1 ]
#
#If on a reference layout ...
If [ $referenceLayout = 1 ]
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
End If
#
Exit Script [ ]
#
#
#
#END Answer C (cancel)
#
#
#
#BEGIN Answer B (create new media with the camera)
#
#
#
#B) If the user selects the camera option
#ask them if they want to use it to ...
Else If [ Get ( LastMessageChoice ) = 2 ]
# B1) take a picture,
# B2) make a movie,
# B3) or cancel.
Show Custom Dialog [ Message: "Take a picture or make a movie?"; Default Button: “cancel”, Commit: “No”; Button 2:
“movie”, Commit: “No”; Button 3: “picture”, Commit: “No” ]
#
#
#BEGIN Answer B3 (cancel)
#
#
#B3) If the user cancels, then exit the script.
If [ Get ( LastMessageChoice ) = 1 ]
Exit Script [ ]
#
#
#END Answer B3 (cancel)
#
#
#BEGIN Answer B2 (make a movie)
#
#
#B2) If the user clicks 'movie'...
Else If [ Get ( LastMessageChoice ) = 2 ]
#
#Prevent record load scripts and
#and then open new window.
If [ Get ( WindowName ) ≠ "Media" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
New Window [ Name: "Media"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control
Area: “Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#Go to correct media layout.
If [ $referenceLayout = 1 ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else If [ $learnLayout = 1 ]
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
#
#If library was focused on a report table layout,
#then the first testlearn table record will be
#showing and not the report record the user
#was just on (report layouts are tied to alias
#tables of the testlearn table). To insert the
#new media into the correct record, it must first
#be found.
If [ $reportTable = 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
End If
#
#Restart record load scripts.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTestResultRecord ]
End If
#
#Go to the picture field to accept new media.
If [ $referenceLayout = 1 ]
Go to Field [ reference::picture ]
Else If [ $learnLayout = 1 ]
Go to Field [ testlearn::picture ]
End If
#
#Give user access to device's media controls.
#If converting from fp7replace 'unknown' script
#step below with 'Insert from Device' with the
#following options:
# type: Video Camera
# camera: Back; Resolution: full
Insert from Device [ Type: Video Camera; Camera: Back; Resolution: Full ]
#
#
#If the user cancels, the photo field will be
#empty, and the window needs to be closed.
If [ reference::picture = "" and $referenceLayout = 1 ]
#
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
#Close window and exit script.
Close Window [ Current Window ]
Exit Script [ ]
#
#
#If media is never required because this is a
#learn record just close the window.
Else If [ testlearn::picture = "" and $learnLayout = 1 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#
#Allow the user to look at their new media.
Go to Field [ ]
Pause/Resume Script [ Indefinitely ]
Set Variable [ $$ReplaceMeMediaRequired ]
Exit Script [ ]
#
#
#END Answer B2 (make a movie)
#
#
#BEGIN Answer B1 (take a picture)
#
#
#B1) If the user clicks 'picture'...
Else If [ Get ( LastMessageChoice ) = 3 ]
#
#Prevent record load scripts and
#and then open new window.
If [ Get ( WindowName ) ≠ "Media" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
New Window [ Name: "Media"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control
Area: “Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#Go to correct media layout.
If [ $referenceLayout = 1 ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else If [ $learnLayout = 1 ]
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
#
#If library was focused on a report table layout,
#then the first testlearn table record will be
#showing and not the report record the user
#was just on (report layouts are tied to alias
#tables of the testlearn table). To insert the
#new media into the correct record, it must first
#be found.
If [ $reportTable = 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
End If
#
#Restart record load scripts.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTestResultRecord ]
End If
#
#Go to the picture field to accept new media.
If [ $referenceLayout = 1 ]
Go to Field [ reference::picture ]
Else If [ $learnLayout = 1 ]
Go to Field [ testlearn::picture ]
End If
#
#Give user access to device's media controls.
#If converting from fp7replace 'unknown' script
#step below with 'Insert from Device' with the
#following options:
# type: Camera
# camera: Back; Resolution: full
Insert from Device [ Type: Camera; Camera: Back; Resolution: Full ]
#
#
#If the user cancels, the photo field will be
#empty, and the window needs to be closed.
If [ reference::picture = "" and $referenceLayout = 1 ]
#
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
#Close window and exit script.
Close Window [ Current Window ]
Exit Script [ ]
#
#
#If media is never required because this is a
#learn record just close the window.
Else If [ testlearn::picture = "" and $learnLayout = 1 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#
#Allow the user to look at their new media.
Go to Field [ ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#
#END Answer B1 (take a picture)
#
#
#
#END Answer B (create new media with the camera)
#
#
#
#BEGIN Answer A (get media from an iDevice's library)
#
#
#
#A) If the user selects the library option...
Else If [ Get ( LastMessageChoice ) = 3 ]
#
#Prevent record load scripts and
#and then open new window.
If [ Get ( WindowName ) ≠ "Media" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
New Window [ Name: "Media"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area:
“Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#Go to correct media layout.
If [ $referenceLayout = 1 ]
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
Else If [ $learnLayout = 1 ]
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
#
#If library was focused on a report table layout,
#then the first testlearn table record will be
#showing and not the report record the user
#was just on (report layouts are tied to alias
#tables of the testlearn table). To insert the
#new media into the correct record, it must first
#be found.
If [ $reportTable = 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
End If
#
#Restart record load scripts.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTestResultRecord ]
End If
#
#Go to the picture field to accept new media.
If [ $referenceLayout = 1 ]
Go to Field [ reference::picture ]
Else If [ $learnLayout = 1 ]
Go to Field [ testlearn::picture ]
End If
#
#Give user access to device's photo library.
#If converting from fp7replace 'unknown' script
#step below with 'Insert from Device' with the
#following options:
# type: Photo Library
Insert from Device [ Type: Photo Library ]
#
#
#If the user cancels, the photo field will be
#empty, and the window needs to be closed.
If [ reference::picture = "" and $referenceLayout = 1 ]
#
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
#Close window and exit script.
Close Window [ Current Window ]
Exit Script [ ]
#
#
#If media is never required because this is a
#learn record just close the window.
Else If [ testlearn::picture = "" and $learnLayout = 1 ]
Close Window [ Current Window ]
Exit Script [ ]
End If
#
#
#Allow the user to look at their new media.
Go to Field [ ]
Set Variable [ $$ReplaceMeMediaRequired ]
Pause/Resume Script [ Indefinitely ]
Exit Script [ ]
End If
#
#
#
#END Answer A (get media from an iDevice's library)
#
#
#END: iDevice
#
#
#------------------------
#
#
#BEGIN: Desktop/Laptop Computer
#
#
#If the user in on an desktop/laptop computer...
Else If [ Get ( SystemPlatform ) ≠ 3 ]
#
#
#
#NOTE: This sequence of questions may seem
#to be in reverse order, however, FileMaker
#displays sequences of buttons from
#right-to-left instead of left-to-right, so
#LastMessageChoice 1 = right,
#2 = middle, and 3 = left button, thus for the
#dialogue box the user sees we have to deal
#here in reverse order so it reads left to right for
#the user.
#
#
#
#Ask user if they want to
# A) insert a picture from a hard drive,
# B) insert a movie from a hard drive,
# C) or cancel.
Show Custom Dialog [ Message: "Select a picture or movie to insert."; Default Button: “cancel”, Commit: “Yes”; Button 2: “movie”,
Commit: “No”; Button 3: “picture”, Commit: “No” ]
#
#
#BEGIN Answer C (cancel)
#
#
#C) If the user cancels, then halt the script and
#also the showCitationPicture1inNewWindow
#script.
If [ Get ( LastMessageChoice ) = 1 ]
#
#If on a reference layout ...
If [ $referenceLayout = 1 ]
#
#If media is required and there is no media,
#then insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 and reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
End If
#
Exit Script [ ]
#
#
#END Answer C (cancel)
#
#
#BEGIN Answer B (insert movie from a hard drive)
#
#
#B) If the user clicks 'movie'...
Else If [ Get ( LastMessageChoice ) = 2 ]
#
#Prevent record load scripts and
#and then open new window.
If [ Get ( WindowName ) ≠ "Media" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
New Window [ Name: "Media"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4;
Left: Get (ScreenWidth)/4; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area:
“Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#If user is on a reference layout...
If [ Get (LayoutTableName) = "reference" ]
Set Variable [ $referenceLayout; Value:1 ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceSTagMenusPictureWindowEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
End If
#
#If user is on a learn layout...
Else If [ Get (LayoutTableName) = "testLearn"
 or
Get (LayoutTableName) = "testLearnReportTags" ]
Set Variable [ $learnLayout; Value:1 ]
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
#
#If library was focused on a report table layout,
#then the first testlearn table record will be
#showing and not the report record the user
#was just on (report layouts are tied to alias
#tables of the testlearn table). To insert the
#new media into the correct record, it must first
#be found.
If [ $reportTable = 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
End If
#
#Restart record load scripts.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTestResultRecord ]
End If
#
#Go to the picture field to accept new media.
If [ $referenceLayout = 1 ]
Go to Field [ reference::picture ]
Else If [ $learnLayout = 1 ]
Go to Field [ testlearn::picture ]
End If
#
#If converting from fp7 file change "Insert file [ ]"
#>> Dialogue options << as follows:
#
# add new dialogue option: COPY AND PASTE THIS TEXT >> "Playable movies mp4, m4v" ; extensions: mp4, m4v
#
# Storage options: SELECT >>> insert <<<
#
# Display: SELECT >>> content of file (when possible) <<<
Insert File [ ]
[ Filters ]
 [ "All Files": ( *.* ) ]
 [ "Playable movies mp4, m4v": ( mp4, m4v ) ]
[ Storage method: Insert ]
[ Display content ]
[ Compression: Never compress ]
#
If [ Get ( LastError ) = 732 ]
Show Custom Dialog [ Message: "This file cannot be inserted because it contains other files. (You could compress/zip
it if you really want to store it here.)"; Default Button: “OK”, Commit: “No” ]
Else If [ Get ( LastError ) = 731 ]
Show Custom Dialog [ Message: "File you are importing from contains no data."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#If the user cancels, the photo field will be
#empty, and the window needs to be closed.
If [ reference::picture = "" and $referenceLayout = 1 ]
#
#If there is reference media the user must have
#clicked the replace button, and now that they
#are canceling, they need to be returned to
#the reference picture layout in the
#Media window, BUT if there is no media,
#then close the Media window.
If [ reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Close Window [ Current Window ]
End If
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 and reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
Exit Script [ ]
Else If [ testlearn::picture = "" and $learnLayout = 1 ]
#
#If there is reference media the user must have
#clicked the replace button, and now that they
#are canceling, they need to be returned to
#the reference picture layout in the
#Media window.
If [ testlearn::kshowReferencedMedia = "" ]
Close Window [ Current Window ]
End If
#
Exit Script [ ]
End If
#
#Allow the user to look at their new media.
Go to Field [ ]
Set Variable [ $$ReplaceMeMediaRequired ]
#
#Remove reference media if user just replaced
#it with media inserted into this learn record.
Set Field [ testlearn::kshowReferencedMedia; "" ]
Exit Script [ ]
#
#
#END Answer B (insert movie from a hard drive)
#
#
#BEGIN Answer A (insert picture from a hard drive)
#
#
#A) If the user clicks 'picture'...
Else If [ Get ( LastMessageChoice ) = 3 ]
#
#Prevent record load scripts and
#and then open new window.
If [ Get ( WindowName ) ≠ "Media" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
New Window [ Name: "Media"; Height: Get (ScreenHeight)/2; Width: Get (ScreenWidth)/2; Top: Get (ScreenHeight)/4;
Left: Get (ScreenWidth)/4; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area:
“Yes”; Resize: “Yes” ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
#
#If user is on a reference layout...
If [ Get (LayoutTableName) = "reference" ]
Set Variable [ $referenceLayout; Value:1 ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceSTagMenusPictureWindowEDIT” (reference) ]
Else
Go to Layout [ “ReferencePictureWindowEDIT” (reference) ]
End If
#
#If user is on a learn layout...
Else If [ Get (LayoutTableName) = "testLearn"
 or
Get (LayoutTableName) = "testLearnReportTags" ]
Set Variable [ $learnLayout; Value:1 ]
Go to Layout [ “LearnPictureWindowEDIT” (testlearn) ]
End If
#
#
#
#If library was focused on a report table layout,
#then the first testlearn table record will be
#showing and not the report record the user
#was just on (report layouts are tied to alias
#tables of the testlearn table). To insert the
#new media into the correct record, it must first
#be found.
If [ $reportTable = 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $picture ]
Perform Find [ ]
End If
#
#Restart record load scripts.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTestResultRecord ]
End If
#
#Go to the picture field to accept new media.
If [ $referenceLayout = 1 ]
Go to Field [ reference::picture ]
Else If [ $learnLayout = 1 ]
Go to Field [ testlearn::picture ]
End If
Insert Picture [ ]
#
If [ Get ( LastError ) = 732 ]
Show Custom Dialog [ Message: "This file cannot be inserted because it contains other files. (You could compress/zip
it if you really want to store it here.)"; Default Button: “OK”, Commit: “No” ]
Else If [ Get ( LastError ) = 731 ]
Show Custom Dialog [ Message: "File you are importing from contains no data."; Default Button: “OK”, Commit: “Yes” ]
Else If [ Get ( LastError ) = 734 ]
Show Custom Dialog [ Message: "This file type cannot be displayed as a picture."; Default Button: “OK”, Commit: “No” ]
Else If [ Get ( LastError ) = 735 ]
Show Custom Dialog [ Message: "This file type will be displayed as a file, unlike these types = bmp, eps (sometimes),
gif, jpeg, jpg, mov, m4v, mp4, pdf, png, psd, sgi, tga, tif, and tiff."; Default Button: “OK”, Commit: “No” ]
End If
#
#If the user cancels, the photo field will be
#empty, and the window needs to be closed.
If [ reference::picture = "" and $referenceLayout = 1 ]
#
#If there is reference media the user must have
#clicked the replace button, and now that they
#are canceling, they need to be returned to
#the reference picture layout in the
#Media window, BUT if there is no media,
#then close the Media window.
If [ reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Close Window [ Current Window ]
End If
#
#If media is required, insert a place holder.
If [ $$ReplaceMeMediaRequired = 1 and reference::showMedia[1] = "" and reference::showMedia[2] = "" ]
Set Field [ reference::picture; "Replace Me. Media Required" ]
Set Variable [ $$ReplaceMeMediaRequired ]
End If
#
#If in inventory mode, turn back on variable that
#allows the user to edit this reference record.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
Exit Script [ ]
Else If [ testlearn::picture = "" and $learnLayout = 1 ]
#
#If there is reference media the user must have
#clicked the replace button, and now that they
#are canceling, they need to be returned to
#the reference picture layout in the
#Media window, BUT if there is no media,
#then close the Media window.
If [ testlearn::kshowReferencedMedia = "" ]
Close Window [ Current Window ]
End If
#
Exit Script [ ]
End If
#
#Allow the user to look at their new media.
Go to Field [ ]
Set Variable [ $$ReplaceMeMediaRequired ]
#
#Remove reference media if user just replaced
#it with media inserted into this learn record.
Set Field [ testlearn::kshowReferencedMedia; "" ]
Exit Script [ ]
End If
#
End If
#
#
#END Answer A (insert picture from a hard drive)
#
#
#END: Desktop/Laptop Computer
#
#
