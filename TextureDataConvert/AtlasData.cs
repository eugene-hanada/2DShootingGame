
using System.Xml.Linq;
using System.Text.RegularExpressions;

namespace TextureDataConvert
{

	internal class AtlasData
	{
		/// <summary> 画像ファイル名 </summary>
		private string imageName_;

		private Dictionary<string, List<TextureData>> textureData_;

		/// <summary> 画像サイズ </summary>
		Vector2 imgSize_;

		public AtlasData(XElement data)
		{
			textureData_ = new Dictionary<string, List<TextureData>>();
			var img = data.Attribute("imagePath");
			if (img == null)
			{
				throw new Exception("imagePathが読み込めませんでした");
			}

			imageName_ = img.Value;
			Console.WriteLine("対象画像は" + imageName_);

			var imgWidth  =data.Attribute("width");
			if (imgWidth == null)
			{
				throw new Exception("画像の幅がしゅとくできませんでした");
			}

			var imgHeight = data.Attribute("height");
			if (imgHeight == null)
			{
				throw new Exception("画像の高さが取得できませんでした");
			}

			imgSize_ = new Vector2(float.Parse(imgWidth.Value), float.Parse(imgHeight.Value));
			Console.WriteLine("対象画像のサイズは"　+ "縦" + imgSize_.x + " 横" + imgSize_.y);

			foreach (var sp in data.Elements())
			{
				if (!LoadData(sp))
				{
					throw new Exception("ロードに失敗");
				}
			}
		}

		public int CalcSum()
		{
			int rtn = imageName_.Length;
			rtn += (int)(imgSize_.x + imgSize_.y);

			foreach (var data in textureData_)
			{
				rtn += data.Key.Length;
				foreach (var tex in data.Value)
				{
					var uvPos = tex.GetPos();
					var wh = tex.GetWH();
					rtn += (int)(uvPos.x + uvPos.y);
					rtn += (int)(wh.x + wh.y);
				}
			}
			return rtn;
		}

		public void Write(BinaryWriter bw)
		{
			bw.Write(imageName_.Length);
			bw.Write(imageName_.ToCharArray());
			imgSize_.Write(bw);

			foreach (var data in textureData_)
			{
				bw.Write(data.Key.Length);
				bw.Write(data.Key.ToCharArray());
				bw.Write(data.Value.ToArray().Length);
				data.Value.Sort((a, b) => a.GetNum() - b.GetNum());
				foreach (var texdata in data.Value)
				{
					texdata.Write(bw);
				}
			}

		}

		private bool LoadData(XElement? sp)
		{
			if (sp == null)
			{
				return false;
			}

			var nameAtr = sp.Attribute("n");
			if (nameAtr != null)
			{
				var name = nameAtr.Value;
				if (name == null)
				{
					return false;
				}
				name = name.Substring(0, name.Length - 4);

				// 0から9で区切る
				string ptn = "[0-9]";
				var result = Regex.Split(name, ptn);
				string keyName = result[0];

				// 数値だけをとる
				ptn = "[^0-9]";
				var numStrs = Regex.Split(name, ptn);

				int num = 0;

				foreach (var nStr in numStrs)
				{
					if (nStr.Length != 0)
					{
						num = Int32.Parse(nStr);
						break;
					}
				}

				// キーがすでにあるかチェック
				if (!textureData_.ContainsKey(keyName))
				{
					textureData_.Add(keyName, new List<TextureData>());
				}

				textureData_[keyName].Add(new TextureData(sp, num));

			}
			return true;
		}



	}
}
