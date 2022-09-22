using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace ConvertAnimationData
{
	internal class AnimationData
	{
		Dictionary<string, List<Animation>> animData_;
		private int sum_;
		public AnimationData(string xmlName, string exportName)
		{
			animData_ = new Dictionary<string, List<Animation>>();
			XElement xml;

			try
			{
				xml = XElement.Load(xmlName);
			}
			catch (Exception )
			{
				Console.WriteLine("xmlファイルの読み込み失敗");
				throw new Exception();
			}

			
			foreach(var dataXml in xml.Elements("AnimationData"))
			{
				var dataName = dataXml.Attribute("Name");
				if (dataName == null)
				{
					throw new Exception();
				}
				animData_[dataName.Value] = new List<Animation>();
				foreach (var animation in dataXml.Elements("Animation"))
				{
					var anim = new Animation(animation);
					if (anim == null)
					{
						throw new Exception();
					}
					animData_[dataName.Value].Add(anim);
				}
			}

			sum_ = animData_.Count;

			var file = File.Create(exportName);
			BinaryWriter bw = new BinaryWriter(file);
			var sig = new char[4];
			sig[0] = 'a';
			sig[1] = 'd';
			sig[2] = 'a';
			sig[3] = 't';
			bw.Write(sig);

			// Sum値を出力
			bw.Write(sum_);

			foreach (var animation in animData_)
			{
				bw.Write(animation.Key.Length);
				bw.Write(animation.Key.ToCharArray());
				bw.Write(animation.Value.Count);
				foreach(var data in animation.Value)
				{
					data.Export(bw);
				}
			}
			bw.Close();
			file.Close();

		}
	   
	}
}
