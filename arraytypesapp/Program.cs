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
    class MyEventSource : EventSource
    {
        public MyEventSource() : base()
        {

        }

        [Event(1)]
        public void MyEvent(int i)
        {
            WriteEvent(1, i);
        }
    }

    class EventPipe
    {
        static readonly Guid EventPipeProfilerGuid = new Guid("2726B5B4-3F88-462D-AEC0-4EFDC8D7B921");

        public static int Main(string[] args)
        {
            MyEventSource myEventSource = new MyEventSource();
            myEventSource.MyEvent(12);

            Console.WriteLine("Collecting...");

            GC.Collect();

            Console.WriteLine("Hi!");

            return -1;
        }
    }
}
