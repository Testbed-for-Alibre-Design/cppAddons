* DISCLAIMER:
 * ALL SOURCE CODE IN THIS PROJECT IS PROVIDED BY ALIBRE INC. FOR
 * DEMONSTRATION PURPOSES ONLY AND ANY EXPRESSED OR IMPLIED WARRANTIES
 * ARE DISCLAIMED. IN NO EVENT SHALL ALIBRE INC. BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE.

INSTRUCTIONS FOR BUILDING AND INSTALLING SelectionSample AddOn
===============================================================

1. Open SampleAddOn.sln in Microsoft Visual Studio (this sample was last built and tested on Visual Studio 2015)

2. Open the include file StdAfx.H. Change the line that reads #import "C:Program Files\Alibre Design\Program\AlibreX_64.tlb" to include the actual file path of AlibreX_64.tlb on your machine. This is usually C:Program Files\Alibre Design\Program unless you installed Alibre Design in a different location.

Similarly, modify the line that reads #include  "C:\Program Files\Alibre Design\Program\AlibreAddOn_64.tlb".

3. Save changes by clicking the File->Save menu command.

4. Next, make sure the Active Solution Configuration is "Release" and the Active Solution Platform is "x64". Click "Build->Rebuild Solution" command to build the sample Addon. This will create the DLL SampleAddon.DLL under "Release" folder. This DLL is meant to be loaded in Alibre's Add-on environment.

5. We are now ready to install the built add-on in its final delivery location:

	a. In Windows Explorer, navigate to your "ProgramData" folder (%PROGRAMDATA%). There, create a subfolder named "Alibre AddOns" if it does not already exist. Finally, below this sub folder, create a new sub folder named say, "SelectionSample".

	b. Next copy the following files from the addon's project folder to the new folder (i.e., %PROGRAMDATA%\Alibre AddOns\SelectionSample) that you just created:
	
	i)  SampleAddOnForTesting.adc
	ii) TestSampleAddOn.ico
	iii)SampleAddOn.dll

Note that we built SampleAddOn.dll in step 4.

6. Review the SampleAddOnForTesting.adc file from the above step using a text editor like NotePad. This adc file has been pre-created for this sample. Note that each add-on needs a GUID to uniquely identify it. Close the file without making any changes.


7. Using a Windows registry viewer like RegEdit.EXE :

	- Navigate to the following registry key:
	  "HKEY_LOCAL_MACHINE\SOFTWARE\Alibre Design Add-Ons"

	- Add a new String Value under this key.

	- Set the Value Name to the guid that is unique to this addon:
	  {3B769D4E-5222-4066-9608-8B4CF93671DD}
	  Note: This should match entry in SampleAddOnForTesting.adc file.

	- Set the Value Data to the addon's installation folder. In this expample, this would be:
	  C:\ProgramData\Alibre AddOns\SelectionSample

	- Close Registry

8. To run this add-on:

	- Launch Alibre Design

	- Open the assembly file, ".\Data\A1.AD_ASM", that is delivered with this add-on project. (Or, you can also open Part file, "P1.AD_PRT")

	- Click the "Add-on" tab on Alibre Design's ribbon. You should see the "Selection Sample AddOn" show up as a drop down menu on the ribbon

	- From the "Selection Sample AddOn" drop down menu, click "Activate UI" menu command. You should see a "Selection Sample AddOn" tab page shown on AD's Explorer pane.

	- Next, from the "Selection Sample AddOn" drop down menu, click "Select Object" command. This will populate the tab page created above with various radio buttons.
	  Click a radio button, say, "Select First Face". Notice that a face gets selected on the graphics window. Try other radio buttons.
	  
	  Place a break point at the method OnSelect() in the file CSelectObjectCommand.CPP perform above steps after launching AD inside the debugger to step through 
	  the add-on's code. Study the implementation there to see how the various entities are selected using AlibreX api.

