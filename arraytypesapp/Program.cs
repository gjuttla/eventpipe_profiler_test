// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Diagnostics.Tracing;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading;

namespace EventPipeTests
{
    [EventData]
    class MyEventDataSubClass
    {
        public string str=> "Hi, this is a nested class string!";
    }

    [EventData]
    class MyEventDataClass
    {
        public int i => 12;
        public float f => 3;
        public string str => "Hi, this is a string!";
        public MyEventDataSubClass subClass => new MyEventDataSubClass();
    };

    class MyEventSource : EventSource
    {
        public MyEventSource() : base(EventSourceSettings.EtwSelfDescribingEventFormat)
        {

        }

        [Event(1)]
        public void MyEvent(int i)
        {
            WriteEvent(1, i);
        }

        [Event(2)]
        public void MyArrayEvent(char ch, int[] intArray, string str, float f)
        {
            WriteEvent(2, ch, intArray, str, f);
        }

        [Event(3)]
        public void MyObjectEvent(MyEventDataClass obj)
        {
            WriteEvent(3, obj);
        }

        [Event(4)]
        public void KeyValueEvent(string SourceName, string EventName, IEnumerable<KeyValuePair<string, string>> Arguments)
        {
            WriteEvent(4, SourceName, EventName, Arguments);
        }
    }

    class EventPipe
    {
        static readonly Guid EventPipeProfilerGuid = new Guid("2726B5B4-3F88-462D-AEC0-4EFDC8D7B921");

        public static int Main(string[] args)
        {
            List<KeyValuePair<string, string>> myList = new List<KeyValuePair<string, string>>()
            {
                KeyValuePair.Create("samplekey", "samplevalue" ),
                KeyValuePair.Create("samplekey2", "samplevalue2")
            };

            MyEventSource myEventSource = new MyEventSource();
            myEventSource.MyArrayEvent('d', Enumerable.Range(0, 120).ToArray(), "Hello from MyEventSource!", 3.0f);
            myEventSource.KeyValueEvent("Source", "Event", myList);
            myEventSource.MyEvent(12);
            myEventSource.MyObjectEvent(new MyEventDataClass());

            Console.WriteLine("Collecting...");

            GC.Collect();

            Console.WriteLine("Hi!");

            return -1;
        }
    }
}
