The DeltaTimeFilter filters packets with less than or greater delta time from the previous packet

The DeltaTimeFilter is a plugin for Omnipeek that is written in C++ and built with Visual Studio 2017.

If you want to just install the latest binary version of the plugin, it is here:

[Binary DeltaTimeFilter plugin dll](https://liveaction.box.com/s/txsbln487o2z8vpjhw7qyru0jt9orahz)

To use the DeltaTimeFilter first download or build it, and copy the DeltaTimeFilter.dll into your Omnipeek folder.

This folder is here by default: "c:\program files\liveaction\omnipeek\plugins" 

Run Omnipeek, and create a new advanced filter called a DeltaTimeFilter. In the filter create an "Analysis Module" filter node, and select the DeltaTimeFilter.

![](https://github.com/spacepacket/DeltaTimeFilter/blob/main/doc/DeltaTimeFilter-1.png)

Open a file in Omnipeek, navigate to the DeltaTimeFilter tab on the lower left-hand side of the vertical nav bar.

In the Delta Time field enter some number of milliseconds, and select less than or greater than. Greater than is more common, since it will find packets that have a greater delta time than than the previous packet, indicating higher latency.

![](https://github.com/spacepacket/DeltaTimeFilter/blob/main/doc/DeltaTimeFilter-2.png)

In the filter bar select or type filter and specify the DeltaTimeFilter

![](https://github.com/spacepacket/DeltaTimeFilter/blob/main/doc/DeltaTimeFilter-3.png)

When the filter is applied (hit Return) a dialog will appear showing the number of packets selected, and ask what to do with them. If highlight is selected, each packet matching the delta time specified in the filter will be highlighted. 

By adding the Delta Time column the delta time from the previous packet will be obvious.

![](https://github.com/spacepacket/DeltaTimeFilter/blob/main/doc/DeltaTimeFilter-4.png)


