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
		private List<Data> dataList_;

		public Animation(XElement xml)
		{
			var name = xml.Attribute("Name");
			if (name == null)
			{
				throw new Exception("Nameがありません");
			}
			name_ = name.Value;

			var loop = xml.Attribute("loop");
			if (loop == null)
			{
				throw new Exception("loopがありません");
			}
			loop_ = Int32.Parse(loop.Value);

			dataList_ = new List<Data>();
			foreach(var atr in xml.Elements("Data"))
			{
				var str = atr.Value;
				var array = str.Split(',');
				dataList_.Add(new Data(Int32.Parse(array[0]), float.Parse(array[1])));
			}
		}

		public bool Export(BinaryWriter bw)
		{
			bw.Write(name_.Length);
			bw.Write(name_.ToCharArray());
			bw.Write(loop_);
			bw.Write(dataList_.Count);
			foreach (var data in dataList_)
			{
				if (!data.Export(bw))
				{
					return false;
				}
			}
			return true;
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
			public bool Export(BinaryWriter bw)
			{
				bw.Write(idx);
				bw.Write(time_);
				return true;
			}
		 }

	}
}
