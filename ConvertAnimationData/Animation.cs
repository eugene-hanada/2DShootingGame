using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ConvertAnimationData
{
	internal class Animation
	{
		private string name_;
		private int loop_;

		public Animation(XElement xml)
		{
			var name = xml.Element("Name");
			if (name == null)
			{
				throw new Exception("Nameがありません");
			}
			name_ = name.Value;

			var loop = xml.Element("loop");
			if (loop == null)
			{
				throw new Exception("loopがありません");
			}
			loop_ = Int32.Parse(loop.Value);
		}

		struct Data
		{

			public int idx;
			public float time_;

			public Data(int idx, float time)
			{
				this.idx = idx;
				this.time_ = time;
			}

		 }

	}
}
